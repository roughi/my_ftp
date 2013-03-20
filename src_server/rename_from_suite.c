#include "buf_size.h"
#include "my_server.h"
#include "my.h"
#include "xlib.h"

void	rename_to(struct s_static_socket *br)
{
  my_putstr("RNTO REQUEST : It's a lie\n");
  xwrite(br->cs, "503 Must use RNFR first\n", 24);
}

int	access_message(struct s_static_socket *br, char *abso)
{
  if (access(abso, F_OK | R_OK) == -1)
    {
      if (errno == ENOTDIR || errno == ENOENT)
	xwrite(br->cs, "550 No such file or directory\n", 30);
      else
	if (errno == EACCES || errno == EROFS)
	  xwrite(br->cs, "550 Permission denied\n", 22);
	else
	  xwrite(br->cs, "550 Impossible to access the file\n", 34);
      return (-1);
    }
  return (0);
}

void	launch_rename(char *abso, char *rento, struct s_static_socket *br)
{
  if (rename(abso, rento) == -1)
    {
      if (errno == ENOENT || errno == ENOTDIR)
	xwrite(br->cs, "550 No such file or directory\n", 30);
      else
	xwrite(br->cs, "550 Impossible to rename the file\n", 34);
    }
  else
    xwrite(br->cs, "250 Rename successful\n", 22);
}

int	get_rename_to_stat_check(char *buffer, char *rento,
				 struct s_static_socket *br)
{
  if (strncmp(buffer, "RNTO", 4) != 0)
    {
      xwrite(br->cs, "503 Expected RNTO command\n", 26);
      return (-1);
    }
  get_abso(rento, buffer);
  errno = 0;
  if (access(rento, F_OK) != -1)
    {
      xwrite(br->cs, "550 File already exist\n", 23);
      return (-1);
    }
  if (errno == EACCES)
    {
      xwrite(br->cs, "550 Permission denied\n", 22);
      return (-1);
    }
  return (0);
}

int	get_rename_to_stat_check_suite(char *temp, struct s_static_socket *br)
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
  if (access(temp, W_OK | R_OK) == -1)
    {
      xwrite(br->cs, "550 Permission denied\n", 22);
      return (-1);
    }
  return (0);
}
