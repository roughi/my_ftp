#include "my_server.h"
#include "xlib.h"
#include "my.h"

void			write_new_connect(struct sockaddr_in *client_sin,
					  int maxclient, int nbclient)
{
  my_putstr("Connection from ");
  my_putstr(inet_ntoa(client_sin->sin_addr));
  my_putchar(':');
  my_put_nbr(ntohs(client_sin->sin_port));
  my_putstr("\nClient connected : ");
  my_put_nbr(nbclient);
  my_putchar('/');
  my_put_nbr(maxclient);
  my_putchar('\n');
}

ino_t			path_inode(int s_fd)
{
  struct	stat	sb;

  if (lstat(".", &sb) == -1)
    {
      my_putstr("Impossible to stat\n");
      xclose(s_fd);
      exit(EXIT_FAILURE);
    }
  return (sb.st_ino);
}

void			set_pgrp()
{
  struct	s_static_info	*info;

  info = static_info(1);
#ifdef __FreeBSD__
  unsigned int	i = 0;
  int		statut = 0;
  for (; (statut = setpgrp(0, i)) == -1 && i < 65535; i++);
  if (statut == -1)
    {
      my_putstr("Impossible to change process group\n");
      exit(EXIT_FAILURE);
    }
#endif
#ifndef __FreeBSD__
  info->pid = setpgrp();
#endif
}

int			main(int argc, char **argv)
{
  struct	s_static_info	*br;
  int		s_fd;
  int		maxclient;

  set_pgrp();
  welcome_msg_server();
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
    {
      my_putstr("Fatal exception\n");
      exit(EXIT_FAILURE);
    }
  s_fd = init_socket(argc, argv);
  maxclient = init_listen(s_fd, argv, argc);
  br = static_info(0);
  br->nbclient = 0;
  br->s_fd = s_fd;
  accept_client(br, maxclient);
  xclose(s_fd);
  exit(EXIT_SUCCESS);
}
