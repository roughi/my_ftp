#include "my_server.h"
#include "buf_size.h"
#include "xlib.h"
#include "my.h"

int				init_pasv_socket(size_t *port)
{
  struct	protoent	*pe;
  struct	sockaddr_in	sin;
  int		sock;

  pe = my_getprotobyname("tcp");
  sock = my_socket(PF_INET, SOCK_STREAM, pe->p_proto);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(*port);
  sin.sin_addr.s_addr = INADDR_ANY;
  bzero(&(sin.sin_zero), 8);
  while ((bind(sock, (struct sockaddr *) &sin, sizeof(sin)) == -1)
	 && errno != EADDRNOTAVAIL)
    {
      *port = *port + 1;
      sin.sin_port = htons(*port);
    }
  if (errno == EADDRNOTAVAIL || listen(sock, 1) == -1)
    {
      my_putstr("Impossible to find adress\n");
      xclose(sock);
      return (-1);
    }
  return (sock);
}

void				send_ip(struct s_static_socket *br)
{
  struct	s_static_info	*info;

  info = static_info(1);
  xwrite(br->cs, "227 Entering Passive Mode (", 27);
  xwrite(br->cs, info->ip1, my_strlen(info->ip1));
  xwrite(br->cs, ",", 1);
  xwrite(br->cs, info->ip2, my_strlen(info->ip2));
  xwrite(br->cs, ",", 1);
  xwrite(br->cs, info->ip3, my_strlen(info->ip3));
  xwrite(br->cs, ",", 1);
  xwrite(br->cs, info->ip4, my_strlen(info->ip4));
  xwrite(br->cs, ",", 1);
}

void		send_port(size_t port, struct s_static_socket *br)
{
  char		*del;
  size_t	mult = 1;
  size_t	rest;

  my_putstr("PASV on port : ");
  my_put_nbr(port);
  my_putstr("\n");
  for (; 256 * (mult + 1) < port; mult++);
  rest = port - (256 * mult);
  del = my_getstr(mult, "0123456789");
  xwrite(br->cs, del, my_strlen(del));
  xwrite(br->cs, ",", 1);
  xfree(del);
  del = my_getstr(rest, "0123456789");
  xwrite(br->cs, del, my_strlen(del));
  xwrite(br->cs, ").\n", 3);
  xfree(del);
}

void	get_host_and_connect(struct s_static_socket *br, int pasvsock,
			     size_t port)
{
  send_ip(br);
  send_port(port, br);
  br->ctrl = pasvsock;
}

void	get_passive_error(struct s_static_socket *br, int pasvsock)
{
  xwrite(br->cs, "451 Internal Server Error\n", 26);
  xclose(pasvsock);
  br->pasv = -1;
}
