#include "my.h"
#include "my_server.h"
#include "xlib.h"
#define BUF_SIZE 4096

void	s_swrite(int sockfd, char *str, int len)
{
  int	i;

  i = 0;
  while (send(sockfd, (void *) str, (size_t) len, 0) == -1 && i <= 5)
    {
      sleep(1);
      i++;
    }
  if (i >= 5)
    {
      my_putstr("# Warning : A client timed out\n");
      close_connection(sockfd, ((static_socket((int) NULL,
					       (struct sockaddr_in *) NULL, 1))->client_sin));
      exit(EXIT_SUCCESS);
    }
}

void	s_sockstr(int sockfd, char *str)
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
  s_swrite(sockfd, str, BUF_SIZE);
}
