#include "xlib.h"
#include "my_client.h"
#include "my.h"

void	get_hostname_connect(char **argv, char *adress)
{
  my_putstr("Host found : ");
  my_putstr(argv[1]);
  my_putstr(" --> ");
  my_putstr(adress);
  my_putstr("\n");
}

void	set_hint(struct addrinfo *hint)
{
  hint->ai_family = AF_INET;
  hint->ai_socktype = SOCK_STREAM;
  hint->ai_protocol = IPPROTO_TCP;
  hint->ai_flags = 0;
  hint->ai_addrlen = 0;
  hint->ai_addr = 0;
  hint->ai_canonname = 0;
  hint->ai_next = 0;
}
