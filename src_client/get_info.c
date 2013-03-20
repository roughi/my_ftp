#include "buf_size.h"
#include "xlib.h"
#include "my.h"

char	*get_info_client(char *dest, char *buffer, ssize_t size)
{
  int	i = 0;
  int	j = 0;

  for (; buffer[i] != ' ' && i < size; i++)
    for (i++; i < size && buffer[i] != '\n' && buffer[i] != '\r';
	 dest[j++] = buffer[i++]);
  dest[j] = '\0';
  return (dest);
}
