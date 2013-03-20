#include "xlib.h"
#include "my.h"
#include "my_client.h"
#include "buf_size.h"

void	reinit_cmd(struct s_static_client *br, fd_set *readfs)
{
  memset(br->buffer, '\0', CMD);
  FD_ZERO(readfs);
  FD_SET(0, readfs);
  FD_SET(br->s_fd, readfs);
}

int		xselect(int nfds, fd_set *readfds, fd_set *writefds,
			fd_set *exceptfds, struct timeval *timeout)
{
  int	ready;

  if ((ready = select(nfds, readfds, writefds, exceptfds, timeout)) == -1)
    kill_client(0);
  return (ready);
}
