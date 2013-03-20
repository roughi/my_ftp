#include "include.h"

int	my_strcmp(char *s1, char *s2)
{
  int	i = 0;

  for (; s1[i]; i++)
    if (s1[i] != s2[i])
      return (s1[i] - s2[i]);
  return (s1[i] - s2[i]);
}
