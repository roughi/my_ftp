#include "my_server.h"
#include "my.h"
#include "xlib.h"
#include "buf_size.h"

void	chmod_failed(struct s_static_socket *br)
{
  if (errno == ENOTDIR || errno == ENOENT)
    xwrite(br->cs, "451 The file does not exist\n", 28);
  else
    if (errno == ENAMETOOLONG)
      xwrite(br->cs, "451 Pathname too long\n", 22);
    else
      if (errno == EACCES || errno == EROFS)
	xwrite(br->cs, "451 Permission denied\n", 22);
      else
	xwrite(br->cs, "451 Chmod failed\n", 17);
}

int	get_chmod_path_info(char *abso, struct s_static_socket *br,
			    char *rep, int i)
{
  if (argument(&(abso[i])) == -1)
    {
      xwrite(br->cs, "501 Syntax error\n", 17);
      return (-1);
    }
  get_info(abso, abso, my_strlen(abso));
  get_abso(rep, abso);
  return (0);
}

void		change_chmod(char *abso, struct s_static_socket *br)
{
  int		i = 0;
  mode_t	mode;
  char		rep[2048];

  mode = 0;
  get_info(abso, abso, my_strlen(abso));
  for (; abso[i] != ' '; i++);
  for (; abso[i] == ' '; i++);
  if (get_chmod(&mode, abso, &i, br) == -1)
    return ;
  if (get_chmod_path_info(abso, br, rep, i) == -1)
    return ;
  if (chmod(rep, mode) == -1)
    {
      chmod_failed(br);
      return ;
    }
  xwrite(br->cs, "200 SITE CHMOD command successful\n", 34);
  return ;
}

void	site_func(char *abso, struct s_static_socket *br)
{
  my_putstr("SITE REQUEST\n");
  my_putstr(abso);
  my_putstr("\n");
  if (strncmp(abso, "SITE CHMOD", 10) == 0)
    change_chmod(abso, br);
  else
    xwrite(br->cs, "501 Require a valid argument\n", 29);
}
