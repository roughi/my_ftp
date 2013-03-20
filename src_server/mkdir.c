#include "my_server.h"
#include "my.h"
#include "xlib.h"
#include "buf_size.h"

int	verif_dir(char *abso, struct s_static_socket *br)
{
  char  pwd[2048];
  char  dir[2048];
  char	temp[2048];
  int	i;
  int	val;
  int	name;

  get_pwd_pop(pwd);
  val = 0;
  i = my_strlen(abso);
  name = i;
  strcpy(temp, abso);
  while (temp[i] != '/' && i > 0)
    i--;
  temp[i] = '\0';
  name = name - i;
  if (xschdir(temp, br->cs) == -1)
    return (-1);
  get_pwd_pop(dir);
  if (my_strlen(dir) + name <= my_strlen(br->relative))
    val = -1;
  if (xschdir(pwd, br->cs) == -1)
    return (-1);
  return (val);
}

void	show_mk_error(struct s_static_socket *br)
{
  if (errno == ENAMETOOLONG)
    xwrite(br->cs, "451 Pathname too long\n", 22);
  else
    if (errno == ENOENT)
      {
	xwrite(br->cs, "451 A component of the path prefix", 34);
	xwrite(br->cs, " does not exist\n", 16);
      }
    else
      if (errno == EACCES)
	xwrite(br->cs, "451 Permission denied\n", 22);
      else
	if (errno == EEXIST)
	  xwrite(br->cs, "451 The path already exist\n", 27);
	else
	  xwrite(br->cs, "451 Path creation failed\n", 25);
}

void	make_dir(char *abso, struct s_static_socket *br)
{
  my_putstr("MKD REQUEST\n");
  if (verif_dir(abso, br) != -1)
    {
      if (mkdir(abso, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) == -1)
	{
	  show_mk_error(br);
	  return ;
	}
      xwrite(br->cs, "257 Path created.\n", 18);
      return ;
    }
  xwrite(br->cs, "451 Path outside your files space.", 35);
  xwrite(br->cs, "or a component of the path prefix does not exist\n.", 49);
}
