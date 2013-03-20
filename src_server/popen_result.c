#include "my_server.h"
#include "my.h"
#include "xlib.h"

FILE				*popen_result(char *cmd)
{
  struct	s_static_socket *br;
		FILE		*stream;

  br = static_socket((int) NULL, (struct sockaddr_in *) NULL, 1);
  if ((stream = popen(cmd, "r")) == NULL)
    {
      my_putstr("popen failed\n");
      xwrite(br->cs, "451 Internal Server Error\n", 26);
      shut_client_socket(0);
    }
  return (stream);
}
