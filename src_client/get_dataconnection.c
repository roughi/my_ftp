#include "my.h"
#include "my_client.h"
#include "buf_size.h"
#include "xlib.h"

int		get_complete_data(struct s_static_client *br,
				  char *buffer, ssize_t size)
{
  char		*temp;
  ssize_t	octet;

  temp = buffer;
  octet = size;
  while (temp[size - 1] != '\n' && (octet + BUF_SIZE) < CMD)
    {
      temp = &(temp[size]);
      size = xrecv(br->s_fd, temp, CMD, 0);
      octet += size;
    }
  if (octet + BUF_SIZE >= CMD)
    {
      my_putstr("ERROR : Too long request. Aborting...\n");
      return (-1);
    }
  temp[size] = '\0';
  return (0);
}

void				get_port(char *buffer,
					 struct s_static_client *br, char *ip)
{
  struct	protoent	*pe;
  int		mult = 0;
  int		add = 0;
  int		i = 0;

  (void) ip;
  while (buffer[i] != ',')
    mult = (mult * 10) + (buffer[i++] - 48);
  i++;
  for (i++; buffer[i] >= '0' && buffer[i] <= '9';
       add = (add * 10) + (buffer[i++] - 48));
  mult = (mult * 256) + add;
  pe = my_getprotobyname("tcp");
  br->pasv = my_socket(PF_INET, SOCK_STREAM, pe->p_proto);
  (br->sin_pasv).sin_family = AF_INET;
  (br->sin_pasv).sin_port = htons(mult);
}

void	get_ip(char *buffer, struct s_static_client *br)
{
  char	ip[16];
  int	i = 0;
  int	j = 0;
  int	nb = 0;

   while (nb < 4 && buffer[i] != '\n' && buffer[i] != '\0')
    {
      if (buffer[i] == ',')
        {
          ip[j++] = '.';
          i++;
          nb++;
        }
      else
        ip[j++] = buffer[i++];
    }
  if (ip[j - 1] == '.')
    ip[j - 1] = '\0';
  ip[j] = '\0';
  (br->sin_pasv).sin_addr.s_addr = inet_addr(ip);
  bzero(&((br->sin_pasv).sin_zero), 8);
  get_port(&(buffer[i]), br, ip);
}

int	parse_port_info(char *buffer, struct s_static_client *br)
{
  int	i = 3;

  for (; buffer[i] && (buffer[i] < '0' || buffer[i] > '9'); i++);
  if (buffer[i] == '\0')
    {
      my_putstr("Invalid dataconnection request\n");
      return (-1);
    }
  get_ip(&(buffer[i]), br);
  return (0);
}

int	get_dataconnection_port(struct s_static_client *br)
{
  if (br->retrieve != -1)
    {
      my_putstr("SUCCESS : Dataconnection info already retrieved\n");
      return (0);
    }
  xwrite(br->s_fd, "PASV\n", 5);
  show_response_complete(br->buffer, br);
  if (strncmp(br->buffer, "227 ", 4) != 0)
    {
      my_putstr("ERROR : Expected PORT response\n");
      return (-1);
    }
  my_putstr("Saving Host dataconnection port...\n");
  if (parse_port_info(br->buffer, br) == -1)
    return (-1);
  return (0);
}
