#include "my.h"
#include "my_client.h"
#include "buf_size.h"
#include "xlib.h"

int				reopen_socket()
{
  struct	protoent	*pe;
  int		s_fd;

  pe = my_getprotobyname("tcp");
  s_fd = my_socket(PF_INET, SOCK_STREAM, pe->p_proto);
  return (s_fd);
}

int				try_to_connect(struct s_static_client *br)
{
  set_sock_options(br->pasv);
  if (connect(br->pasv, (struct sockaddr *) &(br->sin_pasv),
	       sizeof(struct sockaddr)) == -1)
    {
      xclose(br->pasv);
      br->pasv = reopen_socket();
      (br->sin_pasv).sin_addr.s_addr = (br->sin).sin_addr.s_addr;
      if (connect(br->pasv, (struct sockaddr *) &(br->sin_pasv),
		   sizeof(struct sockaddr)) == -1)
	{
	  reset_sock_options(br->pasv);
	  my_putstr("ERROR : Impossible to open dataconnection to try connect\n");
	  return (-1);
	}
    }
  reset_sock_options(br->pasv);
  return (0);
}

void				list_file(struct s_static_client *br)
{
  ssize_t	octet;
  char		buffer[BUF_SIZE];
  char		message[CMD];

  if (get_dataconnection_port(br) == -1)
    return ;
  xwrite(br->s_fd, "LIST", 4);
  if (try_to_connect(br) == -1)
    return ;
  show_response_complete(message, br);
  my_putstr("\n");
  while ((octet = recv(br->pasv, buffer, BUF_SIZE, 0)) > 0)
    xwrite(1, buffer, octet);
  my_putstr("\n");
  if (octet == -1)
    my_putstr("ERROR : Error during data transfer\n");
  xclose(br->pasv);
  br->retrieve = -1;
  br->pasv = -1;
}
