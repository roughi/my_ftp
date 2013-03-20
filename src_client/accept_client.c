#include "buf_size.h"
#include "my_client.h"
#include "xlib.h"
#include "my.h"

void		epur_buffer(char *buffer)
{
  int	i = my_strlen(buffer) - 1;;

  for (; buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t') && i > 0; i--);
  buffer[i + 1] = '\0';
}

void		send_cmd(struct s_static_client *br)
{
  ssize_t	size;

  size = xread(0, br->buffer, CMD);
  br->buffer[size - 1] = '\0';
  epur_buffer(br->buffer);
  check_op(br, br->buffer);
}

void		begin_session(struct s_static_client *br)
{
  fd_set	readfs;

  my_putstr("{ftp} ");
  while (42 == 42)
    {
      reinit_cmd(br, &readfs);
      xselect(br->s_fd + 1, &readfs, NULL, NULL, NULL);
      if (FD_ISSET(br->s_fd, &readfs))
	show_response(br);
      if (FD_ISSET(0, &readfs))
	send_cmd(br);
    }
}

void		connexion_success(struct s_static_client *br)
{
  printf("SUCCESS : Connection to host %s etablished.\n", br->hostname);
}

void		accept_client(struct s_static_client *br)
{
  xconnect(br->s_fd, (struct sockaddr *) &(br->sin),
	   sizeof (struct sockaddr_in));
  connexion_success(br);
  get_auth(br);
  begin_session(br);
  static_info(-1);
  my_putstr("Connection closed\n");
  xclose(br->s_fd);
}
