#include "my.h"

time_t  xtime(time_t *ltime)
{
  if (time(ltime) == (time_t) -1)
    {
      my_putstr("getting time failed\n");
      return ((time_t) 0);
    }
  else
    return (*ltime);
}

void		put_time()
{
  time_t	ltime;
  char		*date;

  if (xtime(&ltime) != (time_t) 0)
      if ((date = ctime(&ltime)) != (char *) NULL && date != (char *) -1)
	my_putstr(date);
}
