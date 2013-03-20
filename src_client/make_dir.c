#include "my.h"
#include "xlib.h"
#include "buf_size.h"
#include "my_client.h"

void	make_dir(char *buffer, struct s_static_client *br)
{
  char	dir[CMD];

  strcpy(dir, "MKD ");
  get_info_c(&(dir[4]), buffer, my_strlen(buffer));
  xwrite(br->s_fd, dir, my_strlen(dir));
}
