#include "my_server.h"
#include "buf_size.h"
#include "xlib.h"
#include "my.h"

void	update_pwd(struct s_static_socket *br)
{
  FILE	*stream;
  char	pwd[4096];
  char	*point;
  int	octet;
  int	i;

  octet = popen_pwd_verification(&stream, pwd, br);
  if (pwd[octet - 1] == '\n')
    pwd[octet - 1] = '\0';
  pwd[octet] = '\0';
  for (i = 0; pwd[i] == br->relative[i] && br->relative[i]; i++);
  point = (char *) &(pwd[i]);
  xfree(br->pwd);
  br->pwd = xmalloc(sizeof(*(br->pwd)) * (my_strlen(point) + 2));
  br->pwd = strcpy(br->pwd, point);
  if (br->pwd[0] == '\0')
    br->pwd = strcpy(br->pwd, "/");
}

void	client_handler_suite(struct s_static_socket *br,
			     char *buffer, ssize_t size)
{
  if (strncmp(buffer, "TYPE A", 6) == 0)
    xwrite(br->cs, "200 Type set to A\n", 18);
  else if (strncmp(buffer, "PASV", 4) == 0)
    entering_passive(br);
  else if (strncmp(buffer, "LIST", 4) == 0)
    get_list(br);
  else if (strncmp(buffer, "CWD", 3) == 0)
    change_working_directory(br, (char *) buffer, size);
  else if (strncmp(buffer, "CDUP", 4) == 0)
    cdup(br);
  else
    {
      xwrite(br->cs, "502 Not implemented\n", 20);
   }
}

void	if_logged(struct s_static_socket *br, char *buffer, ssize_t size)
{
  if (br->islog == 1)
    {
      if (strncmp(buffer, "PWD", 3) == 0)
	list_directory(br);
      else if (strncmp(buffer, "REST", 4) == 0)
	resume(buffer, br);
      else if (strncmp(buffer, "TYPE I", 6) == 0)
	xwrite(br->cs, "200 Type set to I\n", 18);
      else if (check_relative_cmd(buffer, br) == -1)
	client_handler_suite(br, buffer, size);
    }
  else
    xwrite(br->cs, "530 USER must be logged\n", 24);
}

void		client_handler(struct s_static_socket *br)
{
  char		buffer[CMD];
  ssize_t	size;

  size = xsrecv(br->cs, buffer, CMD, 0);
  buffer[size] = '\0';
  if (strncmp(buffer, "USER ", 5) == 0 && br->islog == 0)
    authentification(br, (char *) buffer, size);
  else if (strncmp(buffer, "SYST", 4) == 0)
    systype(br);
  else if (strncmp(buffer, "FEAT", 4) == 0)
    feature(br);
  else
    if_logged(br, buffer, size);
}

void				talk_client(int cs, struct sockaddr_in client_sin,
					    int s_fd)
{
  struct	s_static_socket	*socket;
  pid_t		pid;

  pid = xfork();
  if (pid == 0)
    {
      limit_resources();
      socket = static_socket(cs, &client_sin, 0);
      init_client(socket);
      xclose(s_fd);
      xwrite(socket->cs, "220 Bienvenu sur le serveur de sodomie\n", 39);
      while (42)
	client_handler(socket);
      close_connection(cs, &client_sin);
      exit(EXIT_SUCCESS);
    }
  xclose(cs);
  return ;
}
