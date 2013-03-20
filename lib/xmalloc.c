#include "include.h"

void	*xmalloc(int var1)
{
  void	*tab;

  if ((tab = malloc(var1)) == NULL)
    {
      write(2, "Impossible to allocate Memory\n", 30);
      exit(-1);
    }
  return (tab);
}
