#include "include.h"
#include "xlib.h"

pid_t	xfork(void)
{
  pid_t	pid;

  pid = 0;
  if ((pid = fork()) == -1)
    {
      xwrite(2, "fork failed\n", 12);
      exit(EXIT_FAILURE);
    }
  return (pid);
}
