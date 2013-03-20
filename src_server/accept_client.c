#include "my_server.h"
#include "xlib.h"
#include "my.h"

void				connection_refused(int cs, struct sockaddr_in *client_sin)
{
  s_sockstr(cs, "ERROR : Connection refused : Server is full.\n");
  printf("Connection refused to : %s : %d --> Server is full !\n", inet_ntoa(client_sin->sin_addr), ntohs(client_sin->sin_port));
  xclose(cs);
}

void				accept_client(struct s_static_info *br, int maxclient)
{
  struct	sockaddr_in	client_sin;
  int		client_sin_len;
  int		cs;

  client_sin_len = sizeof(client_sin);
  get_ip(br);
  while (42 == 42)
    {
      if ((cs = my_accept(br->s_fd, (struct sockaddr *) &client_sin,
			  (socklen_t *) &client_sin_len)) != -1)
	{
	  if (br->nbclient < maxclient)
	    {
	      br->nbclient = br->nbclient + 1;
	      write_new_connect(&client_sin, maxclient, br->nbclient);
	      talk_client(cs, client_sin, br->s_fd);
	    }
	  else
	    connection_refused(cs, &client_sin);
	}
    }
}
