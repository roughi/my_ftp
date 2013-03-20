#include "include.h"
void	my_memset_char(char **str, int size, char c)
{
  int	i;

  i = 0;
  while (i < size)
    (*str)[i++] = c;
}
