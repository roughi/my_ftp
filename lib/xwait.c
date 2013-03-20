#include "xlib.h"
#include "my.h"

pid_t	xwait(int *statut)
{
  pid_t	process;

  if ((process = wait(statut)) == -1)
    {
      xwrite(2, "Fatal error when trying to execute the program.\n", 48);
      xwrite(2, "Maybe that pid SIG return is catched by ", 40);
      xwrite(2, "another program.\n", 17);
      return (-1);
    }
  return (process);
}
