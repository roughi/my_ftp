#include "my_client.h"
#include "my.h"

void	welcome_msg_client()
{
  my_putstr("Client My_ftp\tCurrent date is : ");
  put_time();
  my_putstr("\nStarting...\n");
}
