#include "my_client.h"
#include "my.h"
#include "xlib.h"
#include "buf_size.h"

void	rmdir_file(char *buffer, struct s_static_client *br)
{
  char	rm[CMD];

  strcpy(rm, "RMD ");
  get_info_c(&(rm[4]), buffer, my_strlen(buffer));
  xwrite(br->s_fd, rm, my_strlen(rm));
}

void	rm_file(char *buffer, struct s_static_client *br)
{
  char	rm[CMD];

  strcpy(rm, "DELE ");
  get_info_c(&(rm[5]), buffer, my_strlen(buffer));
  xwrite(br->s_fd, rm, my_strlen(rm));
}
