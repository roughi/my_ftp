#include "my.h"
#include "xlib.h"
#define BUF_SIZE 4096

void	swrite(int sockfd, char *str, int len)
{
  int	i;

  i = 0;
  while (send(sockfd, (void *) str, (size_t) len, 0) <= -1 && i <= 5)
    {
      sleep(1);
      i++;
    }
  if (i >= 5)
    {
      xclose(sockfd);
      my_putstr("ERROR : Connection timed out\n");
      exit(EXIT_SUCCESS);
    }
}

void	sockstr(int sockfd, char *str)
{
  char	msg[BUF_SIZE];
  int	i;

  i = 0;
  memset(msg, '\0', (BUF_SIZE - 1));
  while (str[i] != '\0')
    {
      msg[i] = str[i];
      i++;
    }
  swrite(sockfd, str, BUF_SIZE);
}
