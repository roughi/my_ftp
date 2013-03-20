#include "my_server.h"
#include "my.h"
#include "xlib.h"
#include "buf_size.h"

int			check_file_statut_rm(char *abso, int flag,
					     struct s_static_socket *br, char *pwd)
{
  struct	stat	sb;

  if (lstat(abso, &sb) == -1)
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      if (xschdir(pwd, br->cs) == -1)
	return (-1);
      return (-1);
    }
  if (flag == 0)
    {
      if (S_ISDIR(sb.st_mode))
	return (0);
      if (xschdir(pwd, br->cs) == -1)
	return (-1);
      xwrite(br->cs, "550 Not a directory\n", 20);
      return (-1);
    }
  else
    if (statut_dele(&sb, pwd, br) == -1)
      return (-1);
  return (0);
}

int	chdir_to_parent_rm(char *abso, struct s_static_socket *br)
{
  char	parent[2048];
  int	i;

  strcpy(parent, abso);
  i = my_strlen(parent) - 1;
  for (; i > 0 && parent[i] != '/'; i--);
  if (i == 0)
    return (-1);
  parent[i] = '\0';
  if (xschdir(parent, br->cs) == -1)
    return (-1);
  return (0);
}

void	remove_dir(char *abso, struct s_static_socket *br, int flag)
{
  char	pwd[2048];
  char	rm[2048];

  if (flag == 0)
    my_putstr("RMD REQUEST\n");
  else
    my_putstr("DELE REQUEST\n");
  get_pwd_pop(pwd);
  if (flag == 0 && xschdir(abso, br->cs) == -1)
    return ;
  else
    if (flag == 1 && chdir_to_parent_rm(abso, br) == -1)
      return ;
  get_pwd_pop(rm);
  if (check_size(br, rm, pwd, flag) == -1)
    return ;
  else
    {
      if (flag == 1)
	strcpy(rm, abso);
      if (check_file_statut_rm(abso, flag, br, pwd) != -1)
	fork_rm(br, pwd, rm, flag);
    }
}
