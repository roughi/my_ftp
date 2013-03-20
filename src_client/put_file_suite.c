#include "my.h"
#include "my_client.h"
#include "buf_size.h"
#include "xlib.h"

void		open_store(char *message,
			   struct s_static_client *br)
{
  size_t	bytes;
  int		octet;
  char		buffer[BUF_SIZE];
  size_t	downloaded;

  if (put_opening_file(message, &(br->f_fd), br, &bytes) == -1)
    return ;
  downloaded = 0;
  my_putstr("\n");
  while ((octet = xread(br->f_fd, buffer, BUF_SIZE)) > 0)
    {
      up_percent_of_dl(&downloaded, &octet, &bytes);
      xwrite(br->pasv, buffer, octet);
    }
  my_putstr("\n\n");
  xclose(br->pasv);
  xclose(br->f_fd);
  br->retrieve = -1;
  br->pasv = -1;
  br->f_fd = -1;
  if (octet == -1)
    my_putstr("ERROR : Error during data transfer\n");
  show_response_complete(message, br);
  my_putstr("{ftp} ");
}

int	check_preparse_arg(char *buffer, char *message, int flag)
{
  if (buffer[3])
    {
      my_putstr("ERROR : \"put\" need an argument.\n{ftp} ");
      return (-1);
    }
  put_convert(message, buffer, flag);
  if (access(buffer, F_OK | R_OK) == -1)
    {
      my_putstr("ERROR : No such file or directory\n{ftp} ");
      return (-1);
    }
  return (0);
}

int			preparse_put_file(char *buffer, char *message,
					  struct s_static_client *br, int flag)
{
  struct	stat	sb;

  if (check_preparse_arg(buffer, message, flag) == -1)
    return (-1);
  if (lstat(buffer, &sb) == -1
      || S_ISREG(sb.st_mode) == 0)
    {
      my_putstr("ERROR : Not a regular file.\n{ftp} ");
      return (-1);
    }
  if (get_dataconnection_port(br) == -1)
    return (-1);
  xwrite(br->s_fd, message, my_strlen(message));
  if (try_to_connect(br) == -1)
    return (-1);
  return (0);
}

void		put_file(char *buff, struct s_static_client *br, int flag)
{
  char		message[CMD];
  char		prepare[CMD];
  char		buffer[CMD];

  strcpy(buffer, buff);
  if (preparse_put_file(buffer, message, br, flag) == -1)
    return;
  show_response_complete(prepare, br);
  if (prepare[0] == '4' || prepare[0] == '5')
    {
      xclose(br->pasv);
      br->retrieve = -1;
      br->pasv = -1;
      my_putstr("{ftp} ");
      return ;
    }
  if (prepare[0] == '1')
    open_store(buffer, br);
  return ;
}
