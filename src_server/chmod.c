#include "my_server.h"
#include "my.h"
#include "xlib.h"
#include "buf_size.h"

void	set_other(char *abso, int i, mode_t *mode)
{
  if (abso[i] == '1')
    *mode |= S_IXOTH;
  if (abso[i] == '2')
    *mode |= S_IWOTH;
  if (abso[i] == '4')
    *mode |= S_IROTH;
  if (abso[i] == '5')
    *mode |= (S_IROTH | S_IXOTH);
  if (abso[i] == '6')
    *mode |= (S_IROTH | S_IWOTH);
  if (abso[i] == '7')
    *mode |= S_IRWXO;
}

void	set_group(char *abso, int i, mode_t *mode)
{
  if (abso[i] == '1')
    *mode |= S_IXGRP;
  if (abso[i] == '2')
    *mode |= S_IWGRP;
  if (abso[i] == '4')
    *mode |= S_IRGRP;
  if (abso[i] == '5')
    *mode |= (S_IRGRP | S_IXGRP);
  if (abso[i] == '6')
    *mode |= (S_IRGRP | S_IWGRP);
  if (abso[i] == '7')
    *mode |= S_IRWXG;
}

void	set_owner(char *abso, int i, mode_t *mode)
{
  if (abso[i] == '1')
    *mode |= S_IXUSR;
  if (abso[i] == '2')
    *mode |= S_IWUSR;
  if (abso[i] == '4')
    *mode |= S_IRUSR;
  if (abso[i] == '5')
    *mode |= (S_IRUSR | S_IXUSR);
  if (abso[i] == '6')
    *mode |= (S_IRUSR | S_IWUSR);
  if (abso[i] == '7')
    *mode |= S_IRWXU;
}

int	find_chmod(char *abso, int *i, struct s_static_socket *br, mode_t *mode)
{
  if ((abso[*i] < '0' || abso[*i] > '7')
      || (abso[*i + 1] < '0' || abso[*i + 1] > '7')
      || (abso[*i + 2] < '0' || abso[*i + 2] > '7'))
    {
      xwrite(br->cs, "501 Syntax error\n", 17);
      return (-1);
    }
  set_owner(abso, *i, mode);
  set_group(abso, *i + 1, mode);
  set_other(abso, *i + 2, mode);
  return (0);
}

int	get_chmod(mode_t *mode, char *abso, int *i, struct s_static_socket *br)
{
  if (my_strlen(&(abso[*i])) < 3)
    {
      xwrite(br->cs, "501 Syntax error\n", 17);
      return (-1);
    }
  if (find_chmod(abso, i, br, mode) == -1)
    return (-1);
  *i = *i + 3;
  if (abso[*i] != ' ')
    {
      xwrite(br->cs, "501 Syntax error\n", 17);
      return (-1);
    }
  return (0);
}
