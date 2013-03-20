#include "xlib.h"
#include "my.h"
#include "my_client.h"
#include "buf_size.h"

void	lpwd()
{
  pid_t	pid;

  my_putstr("SUCCESS : Working Directory Path\n");
  pid = xfork();
  if (pid == 0)
    execlp("pwd", "pwd", NULL);
  else
    xwait(NULL);
  my_putstr("{ftp} ");
}

void	lls(char *buffer)
{
  char	opt[CMD];
  char	*pointer;
  pid_t	pid;

  get_info_c(opt, buffer, my_strlen(buffer));
  pointer = opt;
  if (opt[0] == '\0')
    pointer = NULL;
  my_putstr("SUCCESS : Working Listing\n");
  pid = xfork();
  if (pid == 0)
    execlp("/bin/sh", "sh", "-c", "ls -la", NULL);
  else
    xwait(NULL);
  my_putstr("{ftp} ");
}

void	lcd(char *buffer)
{
  char	dir[CMD];

  get_info_c(dir, buffer, my_strlen(buffer));
  if (dir[0] == '\0')
    {
      my_putstr("\"lcd\" need an argument\n{ftp} ");
      return ;
    }
  if (chdir(dir) == -1)
    {
      if (errno == EACCES)
	my_putstr("ERROR : Permission denied\n{ftp} ");
      else
	my_putstr("ERROR : No such file or directory\n{ftp} ");
    }
  else
    my_putstr("SUCCESS : Working directory changed\n{ftp} ");
}
