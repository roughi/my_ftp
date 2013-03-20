#include "my_server.h"
#include "my.h"

void				serv_timeout()
{
  struct	s_static_socket	*br;

  br = static_socket((int) NULL, (struct sockaddr_in *) NULL, 1);
  my_putstr("# Warning : Client ");
  my_putstr(inet_ntoa((br->client_sin)->sin_addr));
  my_putstr(":");
  my_putstr(my_getstr(ntohs((br->client_sin)->sin_port), "0123456789"));
  my_putstr(" timed out\n");
  close_connection(br->cs, br->client_sin);
}
