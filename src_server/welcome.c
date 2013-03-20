#include "my.h"

void	welcome_msg_server()
{
  my_putstr("\033[32mServeur My_ftp\033[00m\n\033[33mNous sommes le ");
  put_time();
  my_putstr("\033[00m\n\033[36mDemarrage du serveur...\n");
}
