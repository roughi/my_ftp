#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "include.h"

struct	s_static_client
{
  struct	sockaddr_in	sin;
  struct	sockaddr_in	sin_pasv;
  char		*hostname;
  char		*buffer;
  int		pasv;
  int		retrieve;
  int		s_fd;
  int		f_fd;
};

struct	s_static_client	*static_info(int flag);
struct	protoent	*my_getprotobyname(char *str);
int		my_socket(int domain, int type, int protocol);
int		init_socket(int ac, char **argv);
int		is_ip(char *str);
int		is_only_num(char *str);
int		xconnect(int s, const struct sockaddr *name, socklen_t namelen);
int		xselect(int nfds, fd_set *readfds, fd_set *writefds,
			fd_set *exceptfds, struct timeval *timeout);
int		get_dataconnection_port(struct s_static_client *br);
int		opening_file(char *message, int *fd, struct s_static_client *br);
int		xfflush(FILE *stream);
int		no_bytes(size_t bytes, struct s_static_client *br, int fd);
int		put_opening_file(char *message, int *fd,
				 struct s_static_client *br, size_t *bytes);
int		try_to_connect(struct s_static_client *br);
void		accept_client(struct s_static_client *br);
void		get_hostname(char **argv, struct s_static_client *br, int s_fd);
void		xgethostbyname(char *str, struct s_static_client *br, int s_fd);
void		xgethostbyaddr(char *str, struct s_static_client *br, int s_fd);
void		welcome_msg_client();
void		write_usage();
void		put_time();
void		kill_client(int signal);
void		reinit_cmd(struct s_static_client *br, fd_set *readfs);
void		show_statut(char *buffer);
void		get_auth(struct s_static_client *br);
void		list_file(struct s_static_client *br);
void		show_response_complete(char *buffer, struct s_static_client *br);
void		change_directory(char *buffer, struct s_static_client *br);
void		show_pwd(struct s_static_client *br);
void		get_file(char *buffer, struct s_static_client *br);
void		get_convert(char *message, char *buffer);
void		percent_of_dl(size_t *downloaded , int *octet, size_t *bytes);
void		check_op(struct s_static_client *br, char *buffer);
void		show_statut(char *buffer);
void		show_response(struct s_static_client *br);
void		put_convert(char *message, char *buffer, int flag);
void		up_percent_of_dl(size_t *downloaded , int *octet, size_t *bytes);
void		put_file(char *buffer, struct s_static_client *br, int flag);
void		make_dir(char *buffer, struct s_static_client *br);
void		chmod_file(char *buffer, struct s_static_client *br);
void		rmdir_file(char *buffer, struct s_static_client *br);
void		rm_file(char *buffer, struct s_static_client *br);
void		mv_file(struct s_static_client *br);
void		lls(char *buffer);
void		lcd(char *buffer);
void		lpwd();
char		*get_info_c(char *dest, char *buffer, ssize_t size);
void	show_ls(struct s_static_client *br);
#endif
