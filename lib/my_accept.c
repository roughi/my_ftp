#include "my_server.h"
#include "xlib.h"
#include "my.h"

int	my_accept(int s, struct sockaddr *addr,
		  socklen_t *addrlen)
{
  int	error;
  int	fs;

  error = 0;
  fs = accept(s, addr, addrlen);
  if (fs == -1)
/*       && (error = errno) != ECONNABORTED */
/*       && errno != EINTR) */
    {
      my_putstr(strerror(errno));
      my_putstr("\naccept failed\n");
      exit(EXIT_FAILURE);
    }
  if (error == ECONNABORTED)
    {
      my_putstr("# A connection closed while waiting on the listen queue\n");
      return (-1);
    }
  else
    if (error == EINTR)
      fs = my_accept(s, addr, addrlen);
  return (fs);
}

