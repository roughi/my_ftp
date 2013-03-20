#include "my.h"
#include "xlib.h"
#include "my_server.h"

int	launch_store_path_creation(char *abso, struct s_static_socket *br,
				   int flag, int *fd)
{
  char	name[2050];

  if (flag == 1)
    if (get_new_name_store(abso, br, name) == -1)
      return (-1);
  if (fd_append(br, fd, abso) == -1)
    return (-1);
  set_octet_position(*fd, br);
  xwrite(br->cs, "150 Opening data connection\n", 28);
  if (flag == 1)
    {
      xwrite(br->cs, "250 Transfer Started, file \"", 28);
      xwrite(br->cs, name, my_strlen(name));
      xwrite(br->cs, "\"\n", 2);
    }
  return (0);
}

void	launch_store(char *abso, struct s_static_socket *br, int flag)
{
  char	buffer[8192];
  int	octet;

  if (launch_store_path_creation(abso, br, flag, &(br->f_fd)) == -1)
    return ;
  octet = 0;
  while (br->pasv != -1 && (octet = recv(br->pasv, buffer, 8192, 0)) > 0)
    xwrite(br->f_fd, buffer, octet);
  xclose(br->f_fd);
  br->f_fd = -1;
  if (br->pasv == -1)
    return ;
  close_passive(br);
  if (octet == -1)
    xwrite(br->cs, "451 Error during reception\n", 27);
  else
    xwrite(br->cs, "226 Transfer complete.\n", 23);
}

int	check_store_stat(int i, struct s_static_socket *br, char *temp)
{
  if (i == 0)
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      close_passive(br);
      return (-1);
    }
  temp[i] = '\0';
  if (xschdir(temp, br->cs) == -1)
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      close_passive(br);
      return (-1);
    }
  return (0);
}

void	check_store_path(char *temp, int flag,
			 struct s_static_socket *br, char *abso)
{
  if (my_strlen(temp) < my_strlen(br->relative))
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      close_passive(br);
      return ;
    }
  if (access(temp, W_OK) != -1)
    launch_store(abso, br, flag);
  else
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      close_passive(br);
    }
}

void	store_file(char *abso, struct s_static_socket *br, int flag)
{
  char	pwd[2048];
  char	temp[2048];
  int	i;

  if (open_dataconnection(br) == -1)
    return ;
  if (flag == 0)
    my_putstr("STOR REQUEST\n");
  else
    my_putstr("STOU REQUEST\n");
  get_pwd_pop(pwd);
  strcpy(temp, abso);
  i = my_strlen(temp);
  while (temp[i] != '/' && i > 0)
    i--;
  if (check_store_stat(i, br, temp) == -1)
    return ;
  get_pwd_pop(temp);
  if (xschdir(pwd, br->cs) == -1)
    return ;
  check_store_path(temp, flag, br, abso);
}
