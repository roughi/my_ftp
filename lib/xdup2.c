#include "include.h"
int	xdup2(int oldd, int newd)
{
  if (dup2(oldd, newd) == -1)
    {
      write(1, "dup2 error\n", 11);
      exit(0);
    }
  return (0);
}
