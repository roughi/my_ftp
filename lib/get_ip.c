#include "xlib.h"
#include "my.h"
#include "my_server.h"

void		get_host_ip(struct s_static_info *br, unsigned char *adress)
{
  unsigned int	nb;
  char		*temp;

  nb = (unsigned int) adress[0];
  temp = my_getstr(nb, "0123456789");
  strcpy((char *) br->ip1, temp);
  xfree(temp);
  nb = (unsigned int) adress[1];
  temp = my_getstr(nb, "0123456789");
  strcpy((char *) br->ip2, temp);
  xfree(temp);
  nb = (unsigned int) adress[2];
  temp = my_getstr(nb, "0123456789");
  strcpy((char *) br->ip3, temp);
  xfree(temp);
  nb = (unsigned int) adress[3];
  temp = my_getstr(nb, "0123456789");
  strcpy((char *) br->ip4, temp);
  xfree(temp);
}

void			get_ip(struct s_static_info *br)
{
  struct	hostent	*host;
		char	hostname[256];

  if (gethostname((char *) hostname, 256) != -1)
    {
      if ((host = gethostbyname(hostname)) == NULL)
	{
	  my_putstr("Impossible to find local ip\n");
	  xclose(br->s_fd);
	  exit(EXIT_FAILURE);
	}
      get_host_ip(br, (unsigned char *) (host->h_addr_list)[0]);
    }
  else
    {
      my_putstr("Impossible to find local ip\n");
      xclose(br->s_fd);
      exit(EXIT_FAILURE);
    }
}
