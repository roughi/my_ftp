#include "my.h"

void			limit_resources()
{
  struct	rlimit	rlp;

  if (getrlimit(RLIMIT_CPU, &rlp) == -1)
    my_putstr("Resource limit modification failed in a process.\n");
  else
    {
      rlp.rlim_cur = rlp.rlim_cur / 2;
      rlp.rlim_max = rlp.rlim_max / 2;
      if (setrlimit(RLIMIT_CPU, &rlp) == -1)
	my_putstr("Resource limit modification failed in second part.\n");
    }
}
