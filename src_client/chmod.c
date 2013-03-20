#include "my_client.h"
#include "my.h"
#include "buf_size.h"
#include "xlib.h"

void	chmod_file(char *buffer, struct s_static_client *br)
{
  char	mode[CMD];

  strcpy(mode, "SITE CHMOD ");
  get_info_c(&(mode[11]), buffer, my_strlen(buffer));
  xwrite(br->s_fd, mode, my_strlen(mode));
}
