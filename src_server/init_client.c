
#include "buf_size.h"
#include "my_server.h"
#include "xlib.h"

void	init_client(struct s_static_socket *socket)
{
  socket->login = xmalloc(sizeof(*(socket->login)) * (CMD + 1));
  socket->pass = xmalloc(sizeof(*(socket->pass)) * (CMD + 1));
  socket->pwd = xmalloc(sizeof(*(socket->pwd)) * 2);
  socket->pwd = strcpy(socket->pwd, "/");
  socket->relative = xmalloc(sizeof(*(socket->relative)) * 2048);
  socket->pasv = -1;
  socket->ctrl = -1;
  socket->rest = 0;
  socket->append = 0;
  socket->f_fd = -1;
}
