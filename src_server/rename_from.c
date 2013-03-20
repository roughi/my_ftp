#include "buf_size.h"
#include "my_server.h"
#include "my.h"
#include "xlib.h"

void	get_rename_to(char *abso, struct s_static_socket *br)
{
  char	buffer[CMD];
  char	rento[2048];
  char	temp[2048];
  int	size;

  size = xrecv(br->cs, buffer, CMD, 0);
  if (buffer[size - 1] == '\n')
    buffer[size - 1] = '\0';
  buffer[size] = '\0';
  if (get_rename_to_stat_check(buffer, rento, br) == -1)
    return ;
  strcpy(temp, rento);
  if (get_rename_to_stat_check_suite(temp, br) == -1)
    return ;
  launch_rename(abso, rento, br);
}

int	stat_rename_check(char *temp, char *pwd, struct s_static_socket *br)
{
  int	i;

  i = my_strlen(temp);
  while (i > 0 && temp[i] != '/')
    i--;
  if (i == 0)
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      return (-1);
    }
  temp[i] = '\0';
  if (xschdir(temp, br->cs) == -1)
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      return (-1);
    }
  if (my_strlen(temp) < my_strlen(br->relative))
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      if (xschdir(pwd, br->cs) == -1)
	return (-1);
      return (-1);
    }
  return (0);
}

void	rename_from(char *abso, struct s_static_socket *br)
{
  char	pwd[2048];
  char	temp[2048];

  if (access_message(br, abso) == -1)
    return ;
  get_pwd_pop(pwd);
  strcpy(temp, abso);
  if (stat_rename_check(temp, pwd, br) == -1)
    return ;
  if (xschdir(pwd, br->cs) == -1)
    return ;
  xwrite(br->cs, "350 File or directory exists, ", 30);
  xwrite(br->cs, "ready for destination name.\n", 28);
  get_rename_to(abso, br);
}
