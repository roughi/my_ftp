#include "xlib.h"
#include "my.h"

void	my_getstr_r(int n, char *base, char *str, int *i)
{
  int	deb;
  int	fin;
  int	len;

  len = my_strlen(base);
  fin = n % len;
  deb = (n - fin) / len;
  if (deb != 0)
    my_getstr_r(deb, base, str, i);
  str[*i] = base[fin];
  *i = *i + 1;
}

char	*my_getstr(int n, char *base)
{
  char	*str;
  int	deb;
  int	fin;
  int	len;
  int	i;

  i = 0;
  str = xmalloc(sizeof(*str) * 9);
  len = my_strlen(base);
  fin = n % len;
  deb = (n - fin) / len;
  if (deb != 0)
    my_getstr_r(deb, base, str, &i);
  str[i] = base[fin];
  i++;
  str[i] = '\0';
  return (str);
}
