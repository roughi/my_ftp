#include "my_server.h"
#include "xlib.h"
#include "my.h"

int				open_dataconnection(struct s_static_socket *br)
{
  struct	sockaddr_in	client_sin;
  int		len;

  if (br->ctrl != -1)
    {
      len = sizeof(client_sin);
      br->pasv = my_accept(br->ctrl, (struct sockaddr *) &client_sin,
			   (socklen_t *) &len);
      my_putstr("PASV : ");
      my_putstr(inet_ntoa(client_sin.sin_addr));
      my_putchar(':');
      my_put_nbr(ntohs(client_sin.sin_port));
      my_putstr("\n");
      xclose(br->ctrl);
      br->ctrl = -1;
      return (0);
    }
  else
    {
      xwrite(br->cs, "425 Can't open data connection.\n", 32);
      return (-1);
    }
  return (-1);
}
