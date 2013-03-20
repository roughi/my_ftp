#include "xlib.h"
#include "buf_size.h"
#include "my.h"
#include "my_client.h"

void	kill_client(int __attribute__((unused)) signal)
{
  my_putstr("\nConnection closed\n");
  static_info(-1);
  exit(EXIT_SUCCESS);
}

void	set_static_client(struct s_static_client *info)
{
  info->f_fd = -1;
  info->buffer = xmalloc(sizeof(*(info->buffer)) * CMD);
  info->pasv = -1;
  info->retrieve = -1;
  if (signal(SIGINT, kill_client) == SIG_ERR)
    {
      my_putstr("Fatal exception\n");
      exit(EXIT_FAILURE);
    }
}

struct	s_static_client		*static_info(int flag)
{
  static struct	s_static_client	info;

  if (flag == 0)
    set_static_client(&info);
  else
    if (flag == -1)
      {
	xfree(info.buffer);
	xclose(info.s_fd);
	if (info.f_fd != -1)
	  xclose(info.f_fd);
	if (info.pasv != -1)
	  xclose(info.pasv);
	return ((struct s_static_client *) -1);
      }
  return (&info);
}
