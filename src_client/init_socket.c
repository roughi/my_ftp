#include "my_client.h"
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

void				set_sock_bind(int s_fd, char **argv, int port)
{
  struct	s_static_client	*br;

  br = static_info(1);
  (br->sin).sin_family = AF_INET;
  (br->sin).sin_port = htons(port);
  br->hostname = argv[1];
  if (is_ip(argv[1]) == 0)
    (br->sin).sin_addr.s_addr = inet_addr(argv[1]);
  else
    xgethostbyname(argv[1], br, s_fd);
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
  if (port < 0 || port > 65535 || flag == 1)
    {
      my_putstr("Invalid port number\n");
      xclose(s_fd);
      write_usage();
    }
  printf("- Client using port %s\n", argv[option]);
  set_sock_bind(s_fd, argv, port);
  return (s_fd);
}

int				init_socket(int ac, char **argv)
{
  struct	protoent	*pe;
		int		s_fd;

  s_fd = 0;
  if (ac < 3)
    write_usage();
  else
    {
      welcome_msg_client();
      pe = my_getprotobyname("tcp");
      s_fd = my_socket(PF_INET, SOCK_STREAM, pe->p_proto);
      s_fd = socket_verif(argv, s_fd, 2);
    }
  return (s_fd);
}
