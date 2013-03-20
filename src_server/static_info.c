#include "xlib.h"
#include "my.h"
#include "my_server.h"

struct	s_static_socket		*static_socket(int cs,
					       struct sockaddr_in *client_sin, int flag)
{
  static struct	s_static_socket	socket;

  if (flag == 0)
    {
      socket.islog = 0;
      socket.cs = cs;
      socket.client_sin = client_sin;
      if (signal(SIGINT, SIG_IGN) == SIG_ERR
	  || signal(SIGUSR1, shut_client_socket) == SIG_ERR
	  || signal(SIGCHLD, SIG_DFL) == SIG_ERR
	  || signal(SIGURG, abor_operation) == SIG_ERR)
	{
	  my_putstr("Fatal exception\n");
	  exit(EXIT_FAILURE);
	}
    }
  return (&socket);
}

struct	s_static_info		*static_info(int flag)
{
  static struct	s_static_info	info;

  if (flag == 0)
    {
      if (chdir("./ftp_data") == -1)
	{
	  my_putstr("\"ftp_data\" folder seem to not exist\n");
	  exit(EXIT_FAILURE);
	}
      if (signal(SIGINT, kill_ftp) == SIG_ERR
	  || signal(SIGCHLD, receive_disconnection) == SIG_ERR
	  || signal(SIGUSR1, SIG_IGN) == SIG_ERR)
	{
	  my_putstr("Fatal exception\n");
	  exit(EXIT_FAILURE);
	}
    }
  else
    if (flag == -1)
      {
	xclose(info.s_fd);
	return ((struct s_static_info *) -1);
      }
  return (&info);
}
