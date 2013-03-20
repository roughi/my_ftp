#include "xlib.h"
#include "my.h"
#include "buf_size.h"

ssize_t		ping_content(void *buffer, ssize_t size)
{
  if (size >= 5 && strcmp((char *) buffer, "ping") == 0)
      return (0);
  return (size);
}

ssize_t		xsrecv(int s, void *buf, size_t len, int flags)
{
  ssize_t	size;

  if ((size = recv(s, buf, len, flags)) <= 0)
    {
      if (size == -1 && errno == EAGAIN)
	serv_timeout();
      xclose(s);
      exit(EXIT_FAILURE);
    }
  return (size);
}

ssize_t		xrecv(int s, void *buf, size_t len, int flags)
{
  ssize_t	size;

  if ((size = recvfrom(s, buf, len, flags, NULL, 0)) <= 0)
    {
      if (size == -1 && errno == EAGAIN)
	serv_timeout();
      else
	my_putstr("ERROR : Disconnection. Cause : Host shuted down\n");
      xclose(s);
      exit(EXIT_FAILURE);
    }
  return (size);
}
