
#include "my_server.h"
#include "xlib.h"

void	close_passive(struct s_static_socket *br)
{
  if (br->pasv != -1)
    xclose(br->pasv);
  br->pasv = -1;
}
