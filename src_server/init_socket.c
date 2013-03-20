#include "my_server.h"
#include "my.h"
#include "xlib.h"

int	my_socket(int domain, int type, int protocol)
{
  int	s_fd;

  if ((s_fd = socket(domain, type, protocol)) == -1)
    {
      my_putstr("Socket failed\n");
      exit(EXIT_FAILURE);
    }
  return (s_fd);
}

struct	protoent		*my_getprotobyname(char *str)
{
  struct	protoent	*pe;

  if ((pe = getprotobyname(str)) == NULL)
    {
      my_putstr("Protocol not found.\n");
      exit(EXIT_FAILURE);
    }
  return (pe);
}

void				set_sock_bind(int s_fd, int port)
{
  struct	sockaddr_in	sin;

  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  bzero(&(sin.sin_zero), 8);
  if (bind(s_fd, (struct sockaddr *) &sin, sizeof(sin)) == -1)
    {
      my_putstr("Binding failed.\n");
      my_putstr("Maybe the port is already reserved by another process\n");
      xclose(s_fd);
      exit(EXIT_FAILURE);
    }
}

int	socket_verif(char **argv, int s_fd, int option)
{
  int	flag;
  int	port;

  if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "?") == 0)
    {
      xclose(s_fd);
      write_usage();
    }
  port = my_getnbr(argv[option], &flag);
  if (port < 1024 || port > 65535 || flag == 1)
    {
      my_putstr("Invalid port number\n");
      xclose(s_fd);
      write_usage();
    }
  my_putstr("- Server using port \033[31m");
  my_putstr(argv[option]);
  my_putstr("\033[36m\n");
  set_sock_bind(s_fd, port);
  return (s_fd);
}

int				init_socket(int ac, char **argv)
{
  struct	protoent	*pe;
		int		s_fd;
		int		option;

  pe = my_getprotobyname("tcp");
  s_fd = my_socket(PF_INET, SOCK_STREAM, pe->p_proto);
  if (ac <= 1)
    {
      my_putstr("- Server using port \033[31m1024\033[36m\n");
      set_sock_bind(s_fd, 1024);
    }
  else
    if (ac == 2)
      s_fd = socket_verif(argv, s_fd, 1);
    else
      if ((option = verify_int_option("-port", argv)) == -1)
	{
	  my_putstr("- Server using port \033[31m1024\033[36m\n");
	  set_sock_bind(s_fd, 1024);
	}
      else
	s_fd = socket_verif(argv, s_fd, option);
  return (s_fd);
}
