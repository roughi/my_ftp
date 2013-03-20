#include "include.h"

ssize_t	err_write(int d, const void *buf, size_t nbytes)
{
  int	s;

  if ((s = write(d, buf, nbytes)) == -1)
    {
      write(2, "Impossible to write information\n", 32);
      exit(-1);
    }
  return (nbytes);
}

int	merror(char *str)
{
  int	i;

  for (i = 0; str[i]; i++);
  err_write(2, str, i);
  return (0);
}
