#include "include.h"

int	check_number(char *str, int *i, int *nb, int *point)
{
  if (str[*i] >= '0' && str[*i] <= '9')
    {
      if (*nb < 3)
	*nb = *nb + 1;
      else
	return (-1);
    }
  else
    {
      if (str[*i] == '.' && str[*i + 1] != '.')
	{
	  *point = *point + 1;
	  *nb = 0;
	  return (0);
	}
      else
	return (-1);
    }
  return (0);
}

int	is_ip(char *str)
{
  int	i = 0;
  int	point = 0;
  int	nb = 0;

  for (; str[i]; i++)
    if (check_number(str, &i, &nb, &point) == -1)
      return (-1);
  if (point != 3 || str[i - 1] == '.')
    return (-1);
  return (0);
}
