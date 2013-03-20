#include "my.h"
#include "xlib.h"
#include "my_server.h"

void	set_append(char *buffer, struct s_static_socket *br)
{
  if (strncmp(buffer, "APPE", 4) == 0)
    br->append = 1;
  else
    br->append = 0;
  return ;
}

void	set_octet_position(int fd, struct s_static_socket *br)
{
  if (br->rest <= 0)
    return ;
  if (lseek(fd, br->rest, SEEK_SET) == -1)
    my_putstr("lseek failed, starting at the begining of the file\n");
  br->rest = 0;
}

void	resume(char *buffer, struct s_static_socket *br)
{
  char	bresume[256];
  char	*size;
  int	i;

  my_putstr("REST REQUEST\n");
  get_info(bresume, buffer, my_strlen(buffer));
  i = 0;
  br->rest = 0;
  while (bresume[i] != '\0')
    {
      br->rest = br->rest * 10;
      br->rest = br->rest + (bresume[i] - 48);
      i++;
    }
  size = my_getstr(br->rest, "0123456789");
  xwrite(br->cs, "350 Restarting at ", 18);
  xwrite(br->cs, size, my_strlen(size));
  xwrite(br->cs, ".Send STORE or RETRIEVE to initiate transfer.\n", 46);
  xfree(size);
}
