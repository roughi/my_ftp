#include "xlib.h"
#include "my_server.h"
#include "my.h"
#include "buf_size.h"

void			retrieve_file_launch(char *abso,
					     struct s_static_socket *br, int abor)
{
  struct	stat	sb;
  char	*size;
  int	octet;
  char	buffer[BUF_SIZE];

  if (retrieve_file_launch_pasv_check(br, &(br->f_fd), abso, &sb) == -1)
    return ;
  size = my_getstr(sb.st_size, "0123456789");
  xwrite(br->cs, "150 Opening data connection for file (", 38);
  xwrite(br->cs, size, my_strlen(size));
  xwrite(br->cs, " bytes)\n", 8);
  xfree(size);
  set_octet_position(br->f_fd, br);
  while ((octet = read(br->f_fd, buffer, BUF_SIZE)) > 0 && br->pasv != -1)
    abor = xwrite(br->pasv, buffer, octet);
  close_passive(br);
  xclose(br->f_fd);
  br->f_fd = -1;
  if (abor == 0)
    return;
  if (octet < 0)
    xwrite(br->cs, "451 File I/O failure\n", 21);
  else
    xwrite(br->cs, "226 Transfer complete.\n", 23);
}

int	check_retrieve_stat(struct s_static_socket *br, char *path, int i)
{
  if (i == 0)
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      close_passive(br);
      return (-1);
    }
  if (xschdir(path, br->cs) == -1)
    {
      close_passive(br);
      return (-1);
    }
  get_pwd_pop(path);
  return (0);
}
int	check_retrieve_absolute_path(struct s_static_socket *br,
				     char *path, char *pwd)
{
  if (xschdir(pwd, br->cs) == -1)
    {
      close_passive(br);
      return (-1);
    }
  if (my_strlen(path) < my_strlen(br->relative))
    {
      xwrite(br->cs, "550 No such file or directory\n", 30);
      close_passive(br);
      return (-1);
    }
  return (0);
}

void	show_retrieve_error(struct s_static_socket *br)
{
  close_passive(br);
  if (errno == 0)
    xwrite(br->cs, "550 Not a regular file\n", 23);
  else
    if (errno == ENOTDIR || errno == ENOENT)
      xwrite(br->cs, "550 No such file or directory\n", 30);
    else
      if (errno == EACCES)
	xwrite(br->cs, "550 Permission denied\n", 22);
      else
	xwrite(br->cs, "550 Impossible to retrieve the file\n", 36);
}

void	retrieve_file(char *abso, struct s_static_socket *br)
{
  struct	stat	sb;
  char	path[2048];
  char	pwd[2048];
  int	i;

  my_putstr("RETR REQUEST\n");
  if (open_dataconnection(br) == -1)
    return ;
  get_pwd_pop(pwd);
  strcpy(path, abso);
  i = my_strlen(path);
  while (path[i] != '/' && i > 0)
    i--;
  path[i] = '\0';
  if (check_retrieve_stat(br, path, i) == -1)
    return ;
  if (check_retrieve_absolute_path(br, path, pwd) == -1)
    return ;
  errno = 0;
  if (access(abso, R_OK) != -1 && lstat(abso, &sb) != -1
      && S_ISREG(sb.st_mode))
    retrieve_file_launch(abso, br, 1);
  else
    show_retrieve_error(br);
}
