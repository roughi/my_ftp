#include "my_server.h"
#include "my.h"
#include "xlib.h"

void				reset_abor_signal()
{
  if (signal(SIGURG, abor_operation) == SIG_ERR)
    shut_client_socket(0);
}

void				abor_operation(int signal)
{
  struct	s_static_socket	*br;
  char				buffer[8192];
  int				octet;

  (void) signal;
  my_putstr("ABOR REQUEST\n");
  reset_abor_signal();
  br = static_socket((int) NULL, (struct sockaddr_in *) NULL, 1);
  octet = recv(br->cs, buffer, 8192, 0);
  if (octet <= 0)
    shut_client_socket(0);
  else
    {
      buffer[octet] = '\0';
      if (strncmp(buffer, "ABOR", 4) == 0)
	{
	  if (br->pasv != -1)
	    {
	      xclose(br->pasv);
	      br->pasv = -1;
	      xwrite(br->cs, "226 Operation aborted\n", 22);
	    }
	  else
	    xwrite(br->cs, "226 No operation\n", 17);
	}
    }
}
