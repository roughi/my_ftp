#include "include.h"
#include "xlib.h"
#include "my_server.h"

size_t		xfread(void *ptr, size_t size, size_t nmemb,
		       FILE *stream)
{
  size_t	octet;

  octet = fread(ptr, size, nmemb, stream);
  if (ferror(stream) != 0)
    {
      xwrite(1, "fread failed\n", 13);
      shut_client_socket(0);
    }
  return (octet);
}
