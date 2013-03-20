#include "my_server.h"
#include "buf_size.h"
#include "xlib.h"
#include "my.h"

void	check_cfg(FILE **fd)
{
  if ((*fd = fopen("users.conf", "r")) == NULL)
    {
      my_putstr("Impossible to open users.conf file\n");
      shut_client_socket(0);
    }
}

void		auth_user_message(struct s_static_socket *socket, char *buffer)
{
  ssize_t	size;

  printf("USER : %s\n", socket->login);
  xwrite(socket->cs, "331 Password required\n", 22);
  size = xsrecv(socket->cs, buffer, CMD, 0);
  socket->pass = get_info(socket->pass, (char *) buffer, size);
  printf("PASS : %s\n", socket->pass);
}

void	authentification(struct s_static_socket *socket,
			 char *buffer, ssize_t size)
{
  int	flag = 0;
  int	enter = 0;
  FILE	*fd;

  check_cfg(&fd);
  while (flag == 0)
    {
      if (enter == 1)
	size = xsrecv(socket->cs, buffer, CMD, 0);
      enter = 1;
      flag = 1;
      socket->login = get_info(socket->login, (char *) buffer, size);
      auth_user_message(socket, buffer);
      check_user(&flag, socket, fd);
    }
  do_user_dir(socket);
  xfpurge(fd);
  xfclose(fd);
  xwrite(socket->cs, "230 User logged in\n", 19);
  socket->islog = 1;
}

void	feature(struct s_static_socket *br)
{
  my_putstr("FEAT REQUEST\n");
  xwrite(br->cs, "211 System\n", strlen("211 System\n"));
}

void	list_directory(struct s_static_socket *br)
{
  my_putstr("PWD REQUEST\n");
  xwrite(br->cs, "257 \"", 5);
  xwrite(br->cs, br->pwd, (my_strlen(br->pwd)));
  xwrite(br->cs, "\" is current directory\n", 23);
}
