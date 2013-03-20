#include "include.h"

ssize_t	v_write(int d, const void *buf, size_t nbytes)
{
  int	s;
  s = write(d, buf, nbytes);
  if (s == -1)
    {
      write(2, "Impossible to write information\n", 32);
      exit(-1);
    }
  return (nbytes);
}

int	my_putstr(char *str)
{
  int	i = 0;

  for (; str[i]; i++);
  v_write(1, str, i);
  return (0);
}
