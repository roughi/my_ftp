#include "include.h"

int	calc_getnbr(char *str, int *i, int *flag, int *result)
{
  while (str[*i])
    {
      if (str[*i] < '0' || str[*i] > '9')
	{
	  *flag = -1;
	  return (-1);
	}
      *result = *result * 10;
      *result = *result + (str[*i] - 48);
      *i = *i + 1;
    }
  return (0);
}

int	my_getnbr(char *str, int *flag)
{
  int	neg;
  int	i;
  int	result;

  if (str != NULL)
    {
      result = 0;
      i = 0;
      neg = 0;
      if (str[i] == '-')
	{
	  neg = 1;
	  i++;
	}
      if (calc_getnbr(str, &i, flag, &result) == -1)
	return (-1);
      *flag = 0;
      if (neg == 1)
	result = result * -1;
      return (result);
    }
  *flag = 1;
  return (-1);
}
