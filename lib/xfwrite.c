#include "include.h"
#include "my.h"
#include "xlib.h"

size_t	xfwrite(const void *ptr, size_t size,
		size_t nmemb, FILE *stream)
{
  size_t	omemb;

  if ((omemb = fwrite(ptr, size, nmemb, stream)) < nmemb)
    {
      my_putstr("fwrite failed\n");
      exit(0);
    }
  return (0);
}
