#include "include.h"
#include "xlib.h"
#ifndef __FreeBSD__
#include <stdio_ext.h>
#endif
void	xfpurge(FILE *stream)
{
#ifndef __FreeBSD__
  __fpurge(stream);
#endif
#ifdef __FreeBSD__
  if (fpurge(stream) == EOF)
    {
      xwrite(2, "fpurge failed\n", 14);
      exit(EXIT_FAILURE);
    }
#endif
}

void	xfclose(FILE *stream)
{
  if (fclose(stream) == EOF)
    {
      xwrite(2, "fclose failed\n", 14);
      exit(EXIT_FAILURE);
    }
}

void	xpclose(FILE *stream)
{
  if (pclose(stream) == -1)
    {
      xwrite(2, "pclose failed\n", 14);
      exit(EXIT_FAILURE);
    }
}

int	xclose(int d)
{
  if (close(d) == -1)
    {
      xwrite(2, "Impossible to close the file.", 29);
      xwrite(2, "Maybe the file is already close\n", 33);
      return (-1);
    }
  return (0);
}
