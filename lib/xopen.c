#include "include.h"
#include "xlib.h"

int	xopen(const char *path, int flags)
{
  int	fd;

  if ((fd = open(path, flags)) == -1)
    {
      xwrite(2, "Permission denied\n", 18);
      exit(-1);
    }
  return (fd);
}
