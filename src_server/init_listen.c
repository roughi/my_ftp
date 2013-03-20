#include "my_server.h"
#include "xlib.h"
#include "my.h"

void	set_listen(int s_fd, int maxclient)
{
  if (listen(s_fd, maxclient) == -1)
    {
      xclose(s_fd);
      my_putstr("Impossible to listen.\n");
      exit(EXIT_FAILURE);
    }
}

int	init_listen(int s_fd, char **argv, int ac)
{
  int	maxclient;
  int	flag;
  int	option;

  if (ac < 3 || (option = verify_int_option("-maxclient", argv)) == -1)
    maxclient = 16;
  else
    {
      maxclient = my_getnbr(argv[option], &flag);
      if (maxclient < 0 || maxclient > 128 || flag == 1)
	{
	  xclose(s_fd);
	  write_usage();
	}
    }
  my_putstr("- Maximum connection limitation set at \033[31m");
  my_put_nbr(maxclient);
  my_putstr("\033[36m client\033[00m\n");
  if (maxclient == 0)
    {
      my_putstr("# Warning : maxclient set to 0. ");
      my_putstr("No user will be able to connect !\n");
    }
  set_listen(s_fd, maxclient);
  return (maxclient);
}
