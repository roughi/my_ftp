#include "my_client.h"
#include "buf_size.h"
#include "my.h"
#include "xlib.h"

void	show_pwd(struct s_static_client *br)
{
  char	pwd[CMD];

  xwrite(br->s_fd, "PWD", 3);
  show_response_complete(pwd, br);
  my_putstr("{ftp} ");
}

void	show_ls(struct s_static_client *br)
{
  char	list[CMD];

  xwrite(br->s_fd, "LIST", 4);
  show_response_complete(list, br);
  my_putstr("{ftp} ");
}
