#include "my_server.h"
#include "xlib.h"
#include "my.h"
#include "buf_size.h"

ssize_t		xsrecv(int s, void *buf, size_t len, int flags)
{
  ssize_t	size;

  if ((size = recv(s, buf, len, flags)) <= 0)
    {
      if (size == -1 && errno == EAGAIN)
	serv_timeout();
      else
	recv_close();
      exit(EXIT_FAILURE);
    }
  size = ping_content(buf, size);
  return (size);
}
