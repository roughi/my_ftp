#include "include.h"
int	is_only_num(char *str)
{
  int	i;

  for (i = 0; str[i]; i++)
    if (str[i] < '0' || str[i] > '9')
      return (-1);
  return (0);
}
