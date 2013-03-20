#include "xlib.h"

int	xschdir(char *path, int sock)
{
  if (chdir(path) == -1)
    {
      xwrite(sock, "550 No such file or directory\n", 30);
      return (-1);
    }
  return (0);
}
