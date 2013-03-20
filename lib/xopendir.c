#include "include.h"

DIR	*xopendir(const char *filename, int *flag)
{
  DIR	*file;

  if ((file = opendir(filename)) == NULL)
    {
      *flag = 1;
      return (file);
    }
  return (file);
}
