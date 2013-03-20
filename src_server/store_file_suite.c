#include "my.h"
#include "xlib.h"
#include "my_server.h"

int	fd_append(struct s_static_socket *br, int *fd, char *abso)
{
  if (br->append == 0)
    {
      if ((*fd = open(abso, O_CREAT | O_TRUNC | O_RDWR,
                      S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        {
          xwrite(br->cs, "451 Impossible to create file\n", 30);
          close_passive(br);
          return (-1);
        }
    }
  else
    {
      br->append = 0;
      if ((*fd = open(abso, O_CREAT | O_APPEND | O_RDWR,
                      S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        {
          xwrite(br->cs, "451 Impossible to create file\n", 30);
          close_passive(br);
          return (-1);
        }
    }
  return (0);
}

int	get_new_name_store_suite(char *abso,
				 struct s_static_socket *br, char *name)
{
  int	i;

  for (i = my_strlen(abso); abso[i] != '/' && i > 0; i--);
  if (i == 0)
    {
      close_passive(br);
      return (-1);
    }
  i++;
  strcpy(name, &(abso[i]));
  return (0);
}

int	get_new_name_store(char *abso, struct s_static_socket *br, char *name)
{
  int	i;
  char	*str;
  int	nb = 0;

  for (i = my_strlen(abso); access(abso, F_OK) != -1; nb++)
    {
      str = my_getstr(nb, "0123456789");
      if (my_strlen(str) - i >= 2048)
	{
	  xwrite(br->cs, "451 Impossible to find a new name\n", 34);
	  xfree(str);
	  close_passive(br);
	  return (-1);
	}
      strcpy(&(abso[i]), str);
      xfree(str);
    }
  if (get_new_name_store_suite(abso, br, name) == -1)
    return (-1);
  return (0);
}
