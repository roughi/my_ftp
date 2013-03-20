#include "my_server.h"
#include "buf_size.h"
#include "xlib.h"
#include "my.h"


void		entering_passive(struct s_static_socket *br)
{
  int		pasvsock;
  size_t	port;

  my_putstr("PASV Request\n");
  if (br->pasv == -1 && br->ctrl == -1)
    {
      port = 1025;
      if ((pasvsock = init_pasv_socket(&port)) > -1)
	get_host_and_connect(br, pasvsock, port);
      else
	xwrite(br->cs, "425 Opening data connection failed\n", 35);
    }
  else
    xwrite(br->cs, "125 Data connection already open\n", 33);
}

int	get_list_popen(struct s_static_socket *br, FILE **list)
{
  xwrite(br->cs, "150 Opening ASCII mode data", 27);
  xwrite(br->cs, "connection for file list\n", 25);
  if ((*list = popen("ls -la | grep -v '^total'", "r")) == NULL)
    {
      xclose(br->pasv);
      br->pasv = -1;
      my_putstr("popen error\n");
      xwrite(br->cs, "451 Internal Server Error\n", 26);
      return (-1);
    }
  return (0);
}

void		get_list(struct s_static_socket *br)
{
  FILE		*list;
  char		buffer[BUF_SIZE];
  size_t	octet;

  if (open_dataconnection(br) == -1)
    return ;
  if (br->pasv == -1)
    xwrite(br->cs, "425 Can't open data connection\n", 31);
  else
    {
      my_putstr("LIST REQUEST\n");
      if (get_list_popen(br, &list) == -1)
	return ;
      while ((octet = fread(buffer, 1, BUF_SIZE, list)) > 0)
	xwrite(br->pasv, buffer, octet);
      xclose(br->pasv);
      br->pasv = -1;
      xfpurge(list);
      usleep(500000);
      xwrite(br->cs, "226 Transfer complete\n", 22);
      xpclose(list);
    }
}
