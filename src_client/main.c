#include "my_client.h"
#include "xlib.h"
#include "my.h"

void				close_connect(int __attribute__((unused)) signal)
{
  struct	s_static_client	*br;

  br = static_info(1);
  if (br->s_fd)
    {
      xclose(br->s_fd);
      my_putstr("\nConnection closed\n");
    }
  exit(EXIT_SUCCESS);
}

void	set_sigpipe()
{
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR
      || signal(SIGINT, close_connect) == SIG_ERR)
    {
      my_putstr("Fatal exception\n");
      exit(EXIT_FAILURE);
    }
}

int				main(int ac, char **argv)
{
  struct	s_static_client	*br;

  set_sigpipe();
  br = static_info(0);
  br->s_fd = init_socket(ac, argv);
  accept_client(br);
  exit(EXIT_SUCCESS);
}
