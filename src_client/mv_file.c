#include "my_client.h"
#include "my.h"
#include "xlib.h"
#include "buf_size.h"

void	mv_file(struct s_static_client *br)
{
  int	octet;
  char	ren[CMD];
  char	message[CMD];

  my_putstr("Type filename source : ");
  strcpy(ren, "RNFR ");
  octet = xread(0, &(ren[5]), CMD) + 5;
  if (ren[octet - 1] == '\n')
    ren[octet - 1] = '\0';
  ren[octet] = '\0';
  xwrite(br->s_fd, ren, my_strlen(ren));
  show_response_complete(message, br);
  if (message[0] == '5')
    {
      my_putstr("{ftp} ");
      return ;
    }
  my_putstr("Type filename destination : ");
  strcpy(ren, "RNTO ");
  octet = xread(0, &(ren[5]), CMD) + 5;
  if (ren[octet - 1] == '\n')
    ren[octet - 1] = '\0';
  ren[octet] = '\0';
  xwrite(br->s_fd, ren, my_strlen(ren));
}
