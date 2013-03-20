#include "include.h"

int	verif_int(int *tab, int size)
{
  int	i = 0;

  for (; i < size; i++)
    if (i + 1 < size && tab[i] > tab[i + 1])
      return (-1);
  return (0);
}

void	my_sort_int_tab(int *tab, int size)
{
  int	i = 0;
  int	tmp;

  while (verif_int(tab, size) != 0)
    for (i = 0; i + 1 < size; i++)
      if (tab[i] > tab[i + 1])
	{
	  tmp = tab[i + 1];
	  tab[i + 1] = tab[i];
	  tab[i] = tmp;
	}
}
