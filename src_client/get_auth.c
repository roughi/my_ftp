#include "buf_size.h"
#include "my_client.h"
#include "my.h"
#include "xlib.h"

void	connect_refused()
{
  static_info(-1);
  my_putstr("Connection closed\n");
  exit(EXIT_SUCCESS);
}

void		show_response_complete(char *buffer, struct s_static_client *br)
{
  ssize_t	size;
  ssize_t	octet;
  char		*temp;

  memset(buffer, '\0', CMD);
  temp = buffer;
  size = xrecv(br->s_fd, buffer, CMD, 0);
  octet = size;
  while (temp[size - 1] != '\n' && (octet + BUF_SIZE < CMD))
    {
      temp = &(temp[size]);
      size = xrecv(br->s_fd, temp, CMD, 0);
      octet = octet + size;
    }
  if (buffer[0] == '4' || buffer[0] == '5')
    my_putstr("ERROR : ");
  else
    my_putstr("SUCCESS : ");
  my_putstr(buffer);
}

void		get_login_pass(struct s_static_client *br, char *login,
			       char *pass, char *buffer)
{
  ssize_t	size;

  my_putstr("USER : ");
  strcpy(login, "USER ");
  size = xread(0, &(login[5]), 512) + 5;
  login[size - 1] = '\0';
  xwrite(br->s_fd, login, my_strlen(login));
  show_response_complete(buffer, br);
  my_putstr("PASS : ");
  strcpy(pass, "PASS ");
  size = xread(0, &(pass[5]), 512) + 5;
  pass[size - 1] = '\0';
  xwrite(br->s_fd, pass, my_strlen(pass));
  show_response_complete(buffer, br);
}

void		get_auth(struct s_static_client *br)
{
  char		buffer[CMD];
  char		login[512];
  char		pass[512];
  ssize_t	size;

  size = xrecv(br->s_fd, buffer, CMD, 0);
  buffer[size] = '\0';
  my_putstr(buffer);
  if (size <= 0 ||
      strcmp(buffer, "ERROR : Connection refused : Server is full.\n") == 0)
    {
      my_putstr(buffer);
      connect_refused();
    }
  while (strncmp(buffer, "230", 3) != 0)
    get_login_pass(br, login, pass, buffer);
}
