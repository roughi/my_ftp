#include "my.h"
#include "my_client.h"
#include "buf_size.h"
#include "xlib.h"

void	get_convert(char *message, char *buffer)
{
  char	*temp;

  strcpy(message, "RETR ");
  temp = &(message[5]);
  get_info_c(temp, buffer, my_strlen(buffer));
}

int	opening_file(char *message, int *fd, struct s_static_client *br)
{
  int	i;

  get_info_c(message, message, my_strlen(message));
  for (i = my_strlen(message); i > 0 && message[i] != '/'; i--);
  if (message[i] == '/')
    message = &(message[i + 1]);
  if ((*fd = open(message, O_CREAT | O_TRUNC | O_WRONLY,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    {
      my_putstr("ERROR : Permission denied to create the file\n");
      xclose(br->pasv);
      br->retrieve = -1;
      br->pasv = -1;
      return (-1);
    }
  return (0);
}

int	xfflush(FILE *stream)
{
  if (fflush(stream) == -1)
    {
      my_putstr("Flushing failed\n");
      exit(EXIT_FAILURE);
    }
  return (0);
}

int	no_bytes(size_t bytes, struct s_static_client *br, int fd)
{
  if (bytes == 0)
    {
      xclose(br->pasv);
      xclose(fd);
      br->retrieve = -1;
      br->pasv = -1;
      my_putstr("{ftp} ");
      return (-1);
    }
  return (0);
}

void	percent_of_dl(size_t *downloaded , int *octet, size_t *bytes)
{
  *downloaded = *downloaded + (size_t) *octet;
  printf("\rDownloaded %d Bytes / %d Bytes, %d %%",
	 *downloaded, *bytes, ((*downloaded * 100) / *bytes));
  xfflush(stdout);
}
