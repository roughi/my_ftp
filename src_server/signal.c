#include "xlib.h"
#include "my.h"
#include "my_server.h"

void				shut_client_socket(int __attribute__((unused)) signal)
{
  struct	s_static_socket	*sock;

  sock = static_socket((int) NULL, (struct sockaddr_in *) NULL, 1);
  xfree(sock->login);
  xfree(sock->pwd);
  xfree(sock->pass);
  xfree(sock->relative);
  if (sock->pasv > -1)
    xclose(sock->pasv);
  if (sock->f_fd > -1)
    xclose(sock->f_fd);
  close_connection(sock->cs, sock->client_sin);
  exit(EXIT_SUCCESS);
}

void			reset_sigchld(struct s_static_info *info)
{
  if (signal(SIGCHLD, receive_disconnection) == SIG_ERR)
    {
      my_putstr("Fatal exception\n");
      xclose(info->s_fd);
      exit(EXIT_FAILURE);
    }
  info->nbclient = info->nbclient - 1;
}

void				receive_disconnection(int __attribute__((unused)) signal)
{
  struct	s_static_info	*info;

  if (wait(NULL) == -1)
    {
      my_putstr("Fatal exception\n");
      exit(EXIT_FAILURE);
    }
  info = static_info(1);
  reset_sigchld(info);
}

void				kill_ftp(int __attribute__((unused)) signal)
{
  struct	s_static_info	*info;
		int		statut;

  info = static_info(1);
  statut = 0;
  my_putstr("\nDisconnection of clients...\n");
/* #ifdef __FreeBSD__ */
  xkillpg(0, SIGUSR1);
/* #endif */
/* #ifndef __FreeBSD__ */
/*   xkillpg(info->pid, SIGUSR1); */
/* #endif */
  my_putstr("Connections succesfully closed.\n");
  static_info(-1);
  exit(EXIT_SUCCESS);
}
