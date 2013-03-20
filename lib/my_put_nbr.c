#include "include.h"

unsigned int	my_put_nbr_size(unsigned int nb)
{
  unsigned int  div = -1;
  char          c;
  char          octet = 0;

  nb = nb * -1;
  for (nb = nb * -1; (nb / div) > 9; div = div * 10);
  while (nb <= 0 && div > 0)
    {
      c = nb / div + '0';
      octet++;
      nb = nb % div;
      div = div / 10;
    }
  return (octet);
}

int	my_put_nbr(int nb)
{
  int   div;
  char  c;

  if (nb < 0)
    write(1, "-", 1);
  else
    nb = nb * -1;
  div = -1;
  while (nb / -div < -9)
    div = div * 10;
  while (nb <= 0 && div < 0)
    {
      c = nb / div + '0';
      write(1, &c, 1);
      nb = nb % div;
      div = div / 10;
    }
  return (0);
}
