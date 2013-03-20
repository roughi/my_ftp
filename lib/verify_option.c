#include "include.h"

int	verify_int_option(char *str, char **argv)
{
  int	i = 0;

  for (; argv[i]; i++)
    if (strcmp(str, argv[i]) == 0)
      return (i + 1);
  return (-1);
}
