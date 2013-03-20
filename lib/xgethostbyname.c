#include "xlib.h"
#include "my.h"
#include "my_client.h"

void			xgethostbyname(char *str, struct s_static_client *br,
				       int s_fd)
{
  struct	hostent	*host;

  if ((host = gethostbyname(str)) == NULL)
    {
      my_putstr("ERROR : Specified host not found\n");
      xclose(s_fd);
      exit(EXIT_FAILURE);
    }
  memcpy(&((br->sin).sin_addr.s_addr), host->h_addr_list[0], host->h_length);
}
