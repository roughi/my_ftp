#include "my.h"
#include "xlib.h"

int	xconnect(int s, const struct sockaddr *name, socklen_t namelen)
{
  if (connect(s, name, namelen) == -1)
    {
      my_putstr("Connect Error : Impossible to connect to the specified host\n");
      exit(EXIT_FAILURE);
    }
  return (0);
}
