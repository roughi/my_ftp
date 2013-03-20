#include "my_server.h"
#include "buf_size.h"
#include "xlib.h"
#include "my.h"

void	ferror_stream(struct s_static_socket *br, char *original)
{
  my_putstr("file stream error\n");
  xwrite(br->cs, "451 Internal Server Error\n", 26);
  xfree(original);
}

char	*cwd_popen(struct s_static_socket *br)
{
  FILE	*stream;
  char	*original;
  int	octet;

  if ((stream = popen("pwd", "r")) == NULL)
    {
      my_putstr("popen failed\n");
      xwrite(br->cs, "451 Internal Server Error\n", 26);
      return ((char *) NULL);
    }
  original = xmalloc(sizeof(*original) * 4096);
  octet = fread(original, 1, 4096, stream);
  if (ferror(stream) != 0)
    {
      ferror_stream(br, original);
      return ((char *) NULL);
    }
  if (original[octet - 1] == '\n')
    original[octet - 1] = '\0';
  original[octet] = '\0';
  xfpurge(stream);
  xpclose(stream);
  return (original);
}

int	check_path_cwd(char **buffer, struct s_static_socket *br)
{
  if ((*buffer)[0] == '/')
    {
      if (chdir(br->relative) == -1)
	{
	  my_putstr("changedir failed\n");
	  xwrite(br->cs, "451 Internal Server Error\n", 26);
	  return (-1);
	}
      return (1);
    }
  return (0);
}

int	cwd_not_parent_first(char *temp,
			     struct s_static_socket *br, char *original)
{
  if (chdir(temp) == -1)
    {
      if (chdir(original) == -1)
	{
	  xfree(original);
	  xwrite(br->cs, "451 Internal Server Error\n", 26);
	  shut_client_socket(0);
	}
      xwrite(br->cs, "550 No such file or directory\n", 30);
      return (-1);
    }
  return (0);
}

int	cwd_not_parent(char *temp, struct s_static_socket *br,
		       char *original, ino_t ino)
{
  if (strcmp(temp, "..") != 0)
    {
      if (cwd_not_parent_first(temp, br, original) == -1)
	return (-1);
    }
  else
    if (ino != br->inode)
      {
	if (chdir("..") == -1)
	  {
	    if (chdir(original) == -1)
	      {
		xfree(original);
		xwrite(br->cs, "451 Internal Server Error\n", 26);
		shut_client_socket(0);
	      }
	    xwrite(br->cs, "550 No such file or directory\n", 30);
	    return (-1);
	  }
      }
  return (0);
}
