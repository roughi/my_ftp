#include "include.h"

void		xfree(void *ptr)
{
  if (ptr != NULL)
    free(ptr);
}
