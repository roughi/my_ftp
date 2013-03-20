#include "my.h"

int	my_putstrl(char *str, ssize_t len)
{
  v_write(1, str, len);
  return (0);
}
