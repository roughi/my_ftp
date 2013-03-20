#include "my_server.h"
#include "my.h"
#include "xlib.h"
#include "buf_size.h"

int	check_relative_cmd_suite(char *buffer, char *abso,
				 struct s_static_socket *br)
{
  if (strncmp(buffer, "RMD", 3) == 0)
    remove_dir(abso, br, 0);
  else
    if (strncmp(buffer, "DELE", 4) == 0)
      remove_dir(abso, br, 1);
    else
      if (strncmp(buffer, "MKD", 3) == 0)
	make_dir(abso, br);
      else
	if (strncmp(buffer, "SITE", 4) == 0)
	  site_func(buffer, br);
	else
	  if (strncmp(buffer, "RNFR", 4) == 0)
	    rename_from(abso, br);
	  else
	    if (strncmp(buffer, "RNTO", 4) == 0)
	      rename_to(br);
	else
	  return (-1);
  return (0);
}

int	check_relative_cmd(char *buffer, struct s_static_socket *br)
{
  char	abso[2048];

  get_abso(abso, buffer);
  set_append(buffer, br);
  if (argument(buffer) != -1)
    {
      if (strncmp(buffer, "RETR", 4) == 0)
	retrieve_file(abso, br);
      else
	if (strncmp(buffer, "STOR", 4) == 0
	    || strncmp(buffer, "APPE", 4) == 0)
	  store_file(abso, br, 0);
	else
	  if (strncmp(buffer, "STOU", 4) == 0)
	    store_file(abso, br, 1);
	  else
	    if (check_relative_cmd_suite(buffer, abso, br) == -1)
	      return (-1);
      br->append = 0;
      my_putstr(abso);
      my_putstr("\n");
    }
  else
    return (-1);
  return (0);
}
