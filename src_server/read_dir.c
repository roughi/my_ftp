#include "my_server.h"
#include "buf_size.h"
#include "xlib.h"
#include "my.h"

char	*get_info(char *dest, char *buffer, ssize_t size)
{
  int	i = 0;
  int	j = 0;

  for (; buffer[i] != ' ' && i < size; i++);
  i++;
  while (i < size && buffer[i] != '\n' && buffer[i] != '\r')
    dest[j++] = buffer[i++];
  dest[j] = '\0';
  return (dest);
}

void		systype(struct s_static_socket *socket)
{
  my_putstr("SYST REQUEST\n");
  xwrite(socket->cs, "215 UNIX\n", 9);
}

void	do_user_dir_access(struct s_static_socket *socket)
{
  if (access(socket->login, F_OK | X_OK | R_OK | W_OK) == -1)
    if (mkdir(socket->login, S_IRWXU | S_IRGRP | S_IXGRP
	      | S_IROTH | S_IXOTH) == -1)
      {
	my_putstr("Impossible to Makedir\n");
	xwrite(socket->cs, "550 Impossible to login\n", 24);
	shut_client_socket(0);
      }
}

void	do_user_dir_chdir(struct s_static_socket *socket, FILE **pwd)
{
  if (chdir(socket->login) == -1)
    {
      my_putstr("Impossible to changedir\n");
      xwrite(socket->cs, "550 Impossible to login\n", 24);
      shut_client_socket(0);
    }
  if ((*pwd = popen("pwd", "r")) == NULL)
    {
      my_putstr("popen error\n");
      xwrite(socket->cs, "550 Impossible to login\n", 24);
      shut_client_socket(0);
    }
}

void		do_user_dir(struct s_static_socket *socket)
{
  FILE		*pwd;
  size_t	size;

  do_user_dir_access(socket);
  do_user_dir_chdir(socket, &pwd);
  if ((size = fread(socket->relative, 1, 1024, pwd)) <= 0)
    {
      my_putstr("Error during fread\n");
      xwrite(socket->cs, "550 Impossible to login\n", 24);
      shut_client_socket(0);
    }
  if (socket->relative[size - 1] == '\n')
    socket->relative[size - 1] = '\0';
  socket->relative[size] = '\0';
  socket->inode = path_inode(socket->cs);
  clearerr(pwd);
  xfpurge(pwd);
  xpclose(pwd);
  my_putstr(socket->relative);
  my_putstr("\n");
}
