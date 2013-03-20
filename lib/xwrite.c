#include "include.h"

ssize_t	xwrite(int d, const void *buf, size_t nbytes)
{
  int	s;

  if ((s = write(d, buf, nbytes)) == -1)
    {
      write(2, "Impossible to write information\n", 32);
      exit(-1);
    }
  return (nbytes);
}
