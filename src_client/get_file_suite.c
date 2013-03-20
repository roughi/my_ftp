#include "my.h"
#include "my_client.h"
#include "buf_size.h"
#include "xlib.h"

void		open_retrieve(char *message,
			      struct s_static_client *br, size_t bytes)
{
  int		octet;
  char		buffer[BUF_SIZE];
  size_t	downloaded = 0;

  if (opening_file(message, &(br->f_fd), br) == -1)
    return ;
  my_putstr("\n");
  if (no_bytes(bytes, br, br->f_fd) == -1)
    return ;
  while ((octet = recv(br->pasv, buffer, BUF_SIZE, 0)) > 0)
    {
      percent_of_dl(&downloaded, &octet, &bytes);
      xwrite(br->f_fd, buffer, octet);
    }
  my_putstr("\n\n");
  if (octet == -1)
    my_putstr("ERROR : Error during data transfer\n");
  my_putstr("{ftp} ");
  xclose(br->pasv);
  xclose(br->f_fd);
  br->retrieve = -1;
  br->pasv = -1;
  br->f_fd = -1;
}

int	preparse_get_file(char *buffer, char *message,
			  struct s_static_client *br)
{
  if (buffer[3] == '\0')
    {
      my_putstr("ERROR : \"get\" need an argument.\n{ftp} ");
      return (-1);
    }
  get_convert(message, buffer);
  if (get_dataconnection_port(br) == -1)
    return (-1);
  xwrite(br->s_fd, message, my_strlen(message));
  if (try_to_connect(br) == -1)
    return (-1);
  return (0);
}

size_t		get_bytes(char *message)
{
  size_t	bytes = 0;
  char		temp[CMD];
  int		i = 0;

  get_info_c(temp, message, my_strlen(message));
  for (; temp[i] && (temp[i] < '0' || temp[i] > '9'); i++);
  for (; temp[i] >= '0' && temp[i] <= '9';
       i++, bytes *= 10, bytes += (temp[i] - 48));
  return (bytes);
}

void		get_file(char *buffer, struct s_static_client *br)
{
  size_t	bytes;
  char		message[CMD];
  char		prepare[CMD];

  if (preparse_get_file(buffer, message, br) == -1)
    return ;
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
    {
      bytes = get_bytes(prepare);
      open_retrieve(message, br, bytes);
    }
  return ;
}
