#include "include.h"

int	my_strncmp(char *s1, char *s2, int n)
{
  int	i = 0;

  for (; (i < n) && s1[i]; i++)
    if (s1[i] != s2[i])
      return (s1[i] - s2[i]);
  return (0);
}
