#include "buf_size.h"
#include "my.h"
#include "my_client.h"
#include "xlib.h"

int	client_argument(char *buffer)
{
  int   i = 0;

  for (; buffer[i] && buffer[i] != ' ' && buffer[i] != '\t'; i++);
  for (; buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t'); i++);
  if (buffer[i] == '\0')
    return (-1);
  return (0);
}

char	*get_info_c(char *dest, char *buffer, ssize_t size)
{
  int   i = 0;
  int   j = 0;

  for (; buffer[i] != ' ' && i < size ; i++);
  i++;
  for (; i < size && buffer[i] != '\n' && buffer[i] != '\r';
       dest[j++] = buffer[i++]);
  dest[j] = '\0';
  return (dest);
}

void	change_directory(char *buffer, struct s_static_client *br)
{
  char	cmd[CMD];
  char	*temp;

  if (client_argument(buffer) == -1)
    xwrite(br->s_fd, "CWD /\n", 6);
  else
    {
      strcpy(cmd, "CWD ");
      temp = &(cmd[4]);
      get_info_c(temp, buffer, my_strlen(buffer));
      xwrite(br->s_fd, cmd, my_strlen(cmd));
    }
  show_response_complete(cmd, br);
  my_putstr("{ftp} ");
}
