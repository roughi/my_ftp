#include "include.h"
#include "xlib.h"
#include "my.h"

int	xkillpg(pid_t pid, int sig)
{
  int	res;

  if ((res = killpg(pid, sig)) == -1)
    {
      xwrite(2, "Kill failed\n", 12);
      exit(EXIT_FAILURE);
    }
  return (res);
}
