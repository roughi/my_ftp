#include "buf_size.h"
#include "my_client.h"
#include "xlib.h"
#include "my.h"

void	check_routine(struct s_static_client *br, char *buffer)
{
  if (strncmp(buffer, "mkdir", 5) == 0)
    make_dir(buffer, br);
  else if (strncmp(buffer, "chmod", 5) == 0)
    chmod_file(buffer, br);
  else if (strncmp(buffer, "rmdir", 5) == 0)
    rmdir_file(buffer, br);
  else if (strncmp(buffer, "rm", 2) == 0)
    rm_file(buffer, br);
  else if (strncmp(buffer, "move", 4) == 0)
    mv_file(br);
  else if (strncmp(buffer, "lcd", 3) == 0)
    lcd(buffer);
  else if (strncmp(buffer, "lls", 3) == 0)
    lls(buffer);
  else if (strncmp(buffer, "lpwd", 4) == 0)
    lpwd();
  else
    my_putstr("{ftp} ");
}

void	check_op(struct s_static_client *br, char *buffer)
{
  my_putstr("\n");
  if (strncmp(buffer, "ls", 4) == 0)
    list_file(br);
  else if (strncmp(buffer, "cd", 2) == 0)
    change_directory(buffer, br);
  else if (strncmp(buffer, "pwd", 3) == 0)
    show_pwd(br);
  else if (strncmp(buffer, "get", 3) == 0)
    get_file(buffer, br);
  else if (strncmp(buffer, "putou", 5) == 0)
    put_file(buffer, br, 1);
  else if (strncmp(buffer, "put", 3) == 0)
    put_file(buffer, br, 0);
  else if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "quit") == 0)
    kill_client(0);
  else
    check_routine(br, buffer);
  return ;
}

void	show_statut(char *buffer)
{
  if (buffer[0] == '4' || buffer[0] == '5')
    my_putstr("ERROR : ");
  else
    my_putstr("SUCCESS : ");
}

void		show_response(struct s_static_client *br)
{
  ssize_t	size;

  my_putstr("\r");
  size = xrecv(br->s_fd, br->buffer, CMD, 0);
  show_statut(br->buffer);
  xwrite(1, br->buffer, size);
  while (br->buffer[size - 1] != '\n')
    {
      size = xrecv(br->s_fd, br->buffer, CMD, 0);
      xwrite(1, br->buffer, size);
    }
  my_putstr("{ftp} ");
}
