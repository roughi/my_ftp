#include "my_server.h"
#include "buf_size.h"
#include "xlib.h"
#include "my.h"

void	cwd_buffer_copy(char *buffer, char *temp, int *i)
{
  int	j;

  j = 0;
  while (buffer[*i] != '/' && buffer[*i] != '\0')
    {
      temp[j++] = buffer[*i];
      *i = *i + 1;
    }
  temp[j] = '\0';
  for (; buffer[*i] == '/'; *i = *i + 1);
}

int				recurse_cwd(int *i, char *temp,
					    char *buffer, char *original)
{
  struct	s_static_socket	*br;
  struct	stat		sb;

  br = static_socket((int) NULL, (struct sockaddr_in *) NULL, 1);
  cwd_buffer_copy(buffer, temp, i);
  if (lstat(".", &sb) == -1)
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      return (-1);
    }
  else
    if (cwd_not_parent(temp, br, original, sb.st_ino) == -1)
      return (-1);
  return (0);
}

void				change_working_directory(struct s_static_socket *br,
							 char *buffer, ssize_t size)
{
  struct	s_static_socket	*info;
		char		temp[4096];
		char		*original;
		int		i;

  if ((original = cwd_popen(br)) == (char *) NULL)
    return ;
  if (buffer[size - 1] == '\n')
    buffer[size - 1] = '\0';
  buffer = get_info(buffer, buffer, size);
  info = static_socket((int) NULL, (struct sockaddr_in *) NULL, 1);
  if ((i = check_path_cwd(&buffer, br)) == -1)
    return ;
  while (buffer[i] == '/')
    i++;
  while (buffer[i] != '\0')
    if (recurse_cwd(&i, temp, buffer, original) == -1)
      return ;
  update_pwd(br);
  xfree(original);
  xwrite(br->cs, "250 CWD command successful.\n", 28);
}

void			cdup(struct s_static_socket *br)
{
  struct	stat	sb;

  if (lstat(".", &sb) == -1)
    {
      xwrite(br->cs, "451 Internal Server Error\n", 26);
      return ;
     }
  if (sb.st_ino != br->inode)
    {
      if (chdir("..") == -1)
	{
	  xwrite(br->cs, "451 Internal Server Error\n", 26);
	  return ;
	}
    }
  update_pwd(br);
  xwrite(br->cs, "250 CDUP command successful.\n", 29);
}

int	popen_pwd_verification(FILE **stream, char *pwd,
			       struct s_static_socket *br)
{
  int	octet;

  if ((*stream = popen("pwd", "r")) == NULL)
    {
      my_putstr("popen failed\n");
      xwrite(br->cs, "451 Internal Server Error\n", 26);
      shut_client_socket(0);
    }
  octet = fread(pwd, 1, 4096, *stream);
  if (ferror(*stream) != 0)
    {
      xwrite(br->cs, "451 Internal Server Error\n", 26);
      shut_client_socket(0);
    }
  xfpurge(*stream);
  xpclose(*stream);
  return (octet);
}
