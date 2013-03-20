#include "include.h"

int	xexecve(const char *path, char *const argv[], char *const envp[])
{
  if (execve(path, argv, envp) == -1)
    exit(-1);
  return (0);
}
