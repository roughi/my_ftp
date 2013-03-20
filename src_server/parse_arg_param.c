#include "my_server.h"
#include "my.h"
#include "xlib.h"
#include "buf_size.h"

void		get_pwd_pop(char *pwd)
{
  FILE		*stream;
  size_t	octet;

  stream = popen_result("pwd");
  octet = xfread(pwd, 1, 2048, stream);
  if (pwd[octet - 1] == '\n')
    pwd[octet - 1] = '\0';
  pwd[octet] = '\0';
  xfpurge(stream);
  xpclose(stream);
}

void	if_path_abso(struct s_static_socket *br, char *abso, char *parse)
{
  int	i;
  int	j;

  j = 0;
  strcpy(abso, br->relative);
  i = my_strlen(abso);
  while (parse[j] != '\0' && parse[j] != '\n')
    abso[i++] = parse[j++];
  abso[i] = '\0';
}

void		if_path_not_abso(char *abso, char *parse)
{
  char		pwd[2048];
  int		i;
  int		j;

  j = 0;
  get_pwd_pop(pwd);
  strcpy(abso, pwd);
  i = my_strlen(abso);
  abso[i++] = '/';
  while (parse[j] != '\0' && parse[j] != '\n')
    abso[i++] = parse[j++];
  abso[i] = '\0';
}

void				get_abso(char *abso, char *buffer)
{
  struct	s_static_socket	*br;
		char		parse[CMD];

  br = static_socket((int) NULL, (struct sockaddr_in *) NULL, 1);
  get_info(parse, buffer, my_strlen(buffer));
  if (parse[0] == '/')
    {
      if_path_abso(br, abso, parse);
      return ;
    }
  else
    {
      if_path_not_abso(abso, parse);
      return ;
    }
}

int	argument(char *buffer)
{
  int	i;

  i = 0;
  while (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\0')
    i++;
  while (buffer[i] == ' ' || buffer[i] == '\t')
    i++;
  if (buffer[i] == '\0')
    return (-1);
  return (0);
}
