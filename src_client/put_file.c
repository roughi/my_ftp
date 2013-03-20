#include "my.h"
#include "my_client.h"
#include "buf_size.h"
#include "xlib.h"

void	put_convert(char *message, char *buffer, int flag)
{
  char	*temp;
  int	i;

  if (flag == 0)
    strcpy(message, "STOR ");
  else
    strcpy(message, "STOU ");
  temp = &(message[5]);
  get_info_c(buffer, buffer, my_strlen(buffer));

  for (i = my_strlen(buffer); i > 0 && buffer[i] != '/'; i--);
  if (buffer[i] == '/')
    i++;
  strcpy(temp, &(buffer[i]));
}

int			put_opening_file(char *message, int *fd,
					 struct s_static_client *br, size_t *bytes)
{
  struct	stat	sb;

  *fd = -1;
  if ((*fd = open(message, O_RDONLY)) == -1 || lstat(message, &sb) == -1)
    {
      my_putstr("ERROR : Permission denied to read the file\n");
      xclose(br->pasv);
      br->retrieve = -1;
      br->pasv = -1;
      if (*fd != -1)
	xclose(*fd);
      return (-1);
    }
  *bytes = (size_t) sb.st_size;
  return (0);
}

void	up_percent_of_dl(size_t *downloaded , int *octet, size_t *bytes)
{
  *downloaded = *downloaded + (size_t) *octet;
  printf("\rUploaded %d Bytes / %d Bytes, %d %%",
	 *downloaded, *bytes, ((*downloaded * 100) / *bytes));
  xfflush(stdout);
}
