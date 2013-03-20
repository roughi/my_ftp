#include "xlib.h"
#include "my_server.h"
#include "my.h"
#include "buf_size.h"

int	retrieve_file_launch_pasv_check(struct s_static_socket *br, int *fd,
					char *abso, struct stat *sb)
{
  if (br->pasv == -1)
    {
      xwrite(br->cs, "425 Can't open data connection\n", 31);
      return (-1);
    }
  if ((*fd = open(abso, O_RDONLY)) == -1)
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      close_passive(br);
      return (-1);
    }
  if (lstat(abso, sb) == -1)
    {
      xwrite(br->cs, "451 Internal server error\n", 26);
      xclose(*fd);
      *fd = -1;
      close_passive(br);
      return (-1);
    }
  return (0);
}
