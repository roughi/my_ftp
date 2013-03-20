#include "my_server.h"
#include "my.h"
#include "xlib.h"
#include "buf_size.h"

int	check_size(struct s_static_socket *br, char *rm, char *pwd, int flag)
{
  if ((my_strlen(rm) <= my_strlen(br->relative) && flag == 0)
      || (my_strlen(rm) < my_strlen(br->relative) && flag == 1))
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      if (xschdir(pwd, br->cs) == -1)
	return (-1);
      return (-1);
    }
  return (0);
}

void	end_statut(struct s_static_socket *br)
{
  if (errno == ENOTDIR || errno == ENOENT)
    xwrite(br->cs, "550 No such file or directory\n", 30);
  else
    if (errno == ENOTEMPTY)
      xwrite(br->cs, "550 Directory contain files\n", 28);
    else
      if (errno == EACCES || errno == EROFS)
	xwrite(br->cs, "550 Permission denied\n", 22);
      else
	xwrite(br->cs, "550 RMD failed\n", 15);
}

void	end_remove(struct s_static_socket *br)
{
  if (errno == ENOTDIR || errno == ENOENT)
    xwrite(br->cs, "550 No such file or directory\n", 30);
  else
    if (errno == ENOTEMPTY)
      xwrite(br->cs, "550 Directory contain files\n", 28);
    else
      if (errno == EACCES || errno == EROFS)
	xwrite(br->cs, "550 Permission denied\n", 22);
      else
	xwrite(br->cs, "550 DELE failed\n", 16);
}

void	fork_rm(struct s_static_socket *br, char *pwd, char *rm, int flag)
{
  if (flag == 0)
    {
      if (rmdir(rm) == -1)
	{
	  end_statut(br);
	  if (xschdir(pwd, br->cs) == -1)
	    return ;
	  return ;
	}
    }
  else
    if (remove(rm) == -1)
      {
	end_remove(br);
	if (xschdir(pwd, br->cs) == -1)
	  return ;
	return ;
      }
  if (flag == 0)
    xwrite(br->cs, "250 RMD command successful.\n", 28);
  else
    xwrite(br->cs, "250 DELE command successful.\n", 29);
  if (xschdir(pwd, br->cs) == -1)
    return ;
  return ;
}

int	statut_dele(struct stat *sb, char *pwd, struct s_static_socket *br)
{
  if (S_ISDIR(sb->st_mode))
    {
      xwrite(br->cs, "550 Is a directory\n", 19);
      if (xschdir(pwd, br->cs) == -1)
	return (-1);
      return (-1);
    }
  return (0);
}
