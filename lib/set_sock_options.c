#include "my.h"

void				reset_sock_options(int s_fd)
{
  struct	timeval		tm;

  tm.tv_sec = 0;
  tm.tv_usec = 0;
  s_fd = s_fd;
/* #ifdef __FreeBSD__ */
  if (setsockopt(s_fd, SOL_SOCKET, SO_RCVTIMEO,
		 (void *) &tm, sizeof(tm)) == -1
      || setsockopt(s_fd, SOL_SOCKET, SO_SNDTIMEO,
		    (void *) &tm, sizeof(tm)) == -1)
    {
      my_putstr(strerror(errno));
      my_putstr("\n\n");
      my_putstr("Unable to set socket options\n");
      exit(EXIT_FAILURE);
    }
/* #endif */
}

void				set_sock_options(int s_fd)
{
  struct	timeval		tm;

  tm.tv_sec = 1;
  tm.tv_usec = 0;
  s_fd = s_fd;
/* #ifdef __FreeBSD__ */
  if (setsockopt(s_fd, SOL_SOCKET, SO_RCVTIMEO,
		 (void *) &tm, sizeof(tm)) == -1
      || setsockopt(s_fd, SOL_SOCKET, SO_SNDTIMEO,
		    (void *) &tm, sizeof(tm)) == -1)
    {
      my_putstr(strerror(errno));
      my_putstr("\n\n");
      my_putstr("Unable to set socket options\n");
      exit(EXIT_FAILURE);
    }
/* #endif */
}
