#include "my_server.h"
#include "buf_size.h"
#include "xlib.h"
#include "my.h"

void	close_connection(int cs, struct sockaddr_in *client_sin)
{
  char	*name;
  char	*ntoa;
  char	*port;
  int	i = 17;
  int	j = 0;

  xclose(cs);
  port = my_getstr(ntohs(client_sin->sin_port), "0123456789");
  ntoa = inet_ntoa(client_sin->sin_addr);
  name = xmalloc(sizeof(*name) * (my_strlen(port)
				  + my_strlen(ntoa) + 20));
  name = my_strcpy(name, "Disconnection of ");
  while (ntoa[j] != '\0')
    name[i++] = ntoa[j++];
  j = 0;
  name[i++] = ':';
  while (port[j] != '\0')
    name[i++] = port[j++];
  name[i++] = '\n';
  name[i++] = '\0';
  my_putstr(name);
  xfree(name);
  xfree(port);
}

void	set_user_mem(struct s_static_socket *socket,
		     char *tofind, int *i, char **users)
{
  int	j;

  j = 0;
  while ((socket->login)[*i] != '\0')
    {
      tofind[*i] = (socket->login)[*i];
      *i = *i + 1;
    }
  tofind[*i] = ' ';
  *i = *i + 1;
  while ((socket->pass)[j] != '\0')
    {
      tofind[*i] = (socket->pass)[j++];
      *i = *i + 1;
    }
  tofind[*i] = '\0';
  *users = xmalloc(sizeof(**users) * 1024);
  (*users)[1023] = '\0';

}

int	find_user(char *users, FILE *fd, char *tofind)
{
  int	i;

  while ((users = fgets(users, 1024, fd)) != NULL)
    {
      i = 0;
      while (users[i] != '\0')
	{
	  if (users[i] == '\n')
	    users[i] = '\0';
	  else
	    i++;
	}
      if (strcmp(users, tofind) == 0)
	{
	  xfree(users);
	  xfree(tofind);
	  return (0);
	}
    }
  return (-1);
}

void	restart_check_user(FILE *fd, char *users, char *tofind,
			   struct s_static_socket *socket)
{
  xfree(users);
  xfree(tofind);
  errno = 0;
  rewind(fd);
  if (errno != 0)
    {
      my_putstr("Error of rewind\n");
      xwrite(socket->cs, "451 Internal Server Error\n", 26);
      xfclose(fd);
      shut_client_socket(0);
    }
  xwrite(socket->cs, "530 Incorrect login or password\n", 32);
}

void	check_user(int *flag, struct s_static_socket *socket, FILE *fd)
{
  char	*users;
  char	*tofind;
  int	i;

  i = 0;
  if (strcmp(socket->login, "anonymous") == 0)
    return ;
  else
    {
      tofind = xmalloc(sizeof(char) * 1024);
      set_user_mem(socket, tofind, &i, &users);
      if (find_user(users, fd, tofind) != -1)
	return ;
      *flag = 0;
      restart_check_user(fd, users, tofind, socket);
    }
}
