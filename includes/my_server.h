#ifndef _SERVER_H_
#define _SERVER_H_

#include "include.h"

struct	s_static_socket
{
  struct	sockaddr_in	*client_sin;
  char		*login;
  char		*pass;
  char		*pwd;
  char		*relative;
  ino_t		inode;
  int		pasv;
  int		ctrl;
  off_t		rest;
  int		islog;
  int		append;
  int		cs;
  int		f_fd;
};

struct	s_static_info
{
  char		ip1[4];
  char		ip2[4];
  char		ip3[4];
  char		ip4[4];
  int		s_fd;
  int		nbclient;
  pid_t		pid;
};

struct	protoent	*my_getprotobyname(char *str);
struct	s_static_info	*static_info(int flag);
struct	s_static_socket	*static_socket(int cs, struct sockaddr_in *client_sin,
				       int flag);
int		init_socket(int ac, char **argv);
int		lstat(const char *path, struct stat *buf);
int		init_listen(int s_fd, char **argv, int ac);
int		my_accept(int s, struct sockaddr *addr,
			  socklen_t *addrlen);
int		my_socket(int domain, int type, int protocol);
int		socket_verif(char **argv, int s_fd, int option);
int		verify_int_option(char *str, char **argv);
int		xkillpg(pid_t pid, int sig);
int		pclose(FILE *stream);
int		check_relative_cmd(char *buffer, struct s_static_socket *br);
int		check_path_cwd(char **buffer, struct s_static_socket *br);
int		cwd_not_parent_first(char *temp,
				     struct s_static_socket *br, char *original);
int		cwd_not_parent(char *temp, struct s_static_socket *br,
			       char *original, ino_t ino);
int		get_list_popen(struct s_static_socket *br, FILE **list);
int		init_pasv_socket(size_t *port);
int		popen_pwd_verification(FILE **stream, char *pwd,
				       struct s_static_socket *br);
int		recurse_cwd(int *i, char *temp,
			    char *buffer, char *original);
int		argument(char *buffer);
int		get_chmod(mode_t *mode, char *abso, int *i, struct s_static_socket *br);
int		check_size(struct s_static_socket *br, char *rm, char *pwd, int flag);
int		statut_dele(struct stat *sb, char *pwd, struct s_static_socket *br);
int		retrieve_file_launch_pasv_check(struct s_static_socket *br, int *fd,
						char *abso, struct stat *sb);
int		get_new_name_store(char *abso, struct s_static_socket *br, char *name);
int		get_rename_to_stat_check(char *buffer, char *rento,
					 struct s_static_socket *br);
int		get_rename_to_stat_check_suite(char *temp, struct s_static_socket *br);
int		access_message(struct s_static_socket *br, char *abso);
int		fd_append(struct s_static_socket *br, int *fd, char *abso);
int		open_dataconnection(struct s_static_socket *br);
void		init_client(struct s_static_socket *socket);
void		talk_client(int cs, struct sockaddr_in client_sin,
			    int s_fd);
void		set_sock_bind(int s_fd, int port);
void		write_new_connect(struct sockaddr_in *client_sin,
				  int maxclient, int nbclient);
void		set_listen(int s_fd, int maxclient);
void		kill_ftp(int signal);
void		welcome_msg_server();
void		s_sockstr(int sockfd, char *str);
void		write_usage();
void		accept_client(struct s_static_info *br, int maxclient);
void		shut_client_socket(int signal);
void		receive_disconnection(int signal);
void		close_connection(int cs, struct sockaddr_in *client_sin);
void		limit_resources();
void		recv_close();
void		update_pwd(struct s_static_socket *br);
void		check_user(int *flag, struct s_static_socket *socket, FILE *fd);
void		do_user_dir_access(struct s_static_socket *socket);
void		do_user_dir_chdir(struct s_static_socket *socket, FILE **pwd);
void		do_user_dir(struct s_static_socket *socket);
void		get_passive_error(struct s_static_socket *br, int pasvsock);
void		entering_passive(struct s_static_socket *br);
void		get_list(struct s_static_socket *br);
void		ferror_stream(struct s_static_socket *br, char *original);
void		cwd_buffer_copy(char *buffer, char *temp, int *i);
void		cdup(struct s_static_socket *br);
void		authentification(struct s_static_socket *socket,
				 char *buffer, ssize_t size);
void		feature(struct s_static_socket *br);
void		list_directory(struct s_static_socket *br);
void		systype(struct s_static_socket *socket);
void		remove_dir(char *abso, struct s_static_socket *br, int flag);
void		get_pwd_pop(char *pwd);
void		change_working_directory(struct s_static_socket *br,
					 char *buffer, ssize_t size);
void		get_host_and_connect(struct s_static_socket *br, int pasvsock,
				     size_t port);
void		get_abso(char *abso, char *buffer);
void		get_ip(struct s_static_info *br);
void		make_dir(char *abso, struct s_static_socket *br);
void		site_func(char *abso, struct s_static_socket *br);
void		end_statut(struct s_static_socket *br);
void		end_fork_rm(struct s_static_socket *br, char *pwd,
			    int statut, int flag);
void		fork_rm(struct s_static_socket *br, char *pwd, char *rm, int flag);
void		retrieve_file(char *abso, struct s_static_socket *br);
void		close_passive(struct s_static_socket *br);
void		store_file(char *abso, struct s_static_socket *br, int flag);
void		abor_operation(int signal);
void		rename_to(struct s_static_socket *br);
void		launch_rename(char *abso, char *rento, struct s_static_socket *br);
void		rename_from(char *abso, struct s_static_socket *br);
void		set_octet_position(int fd, struct s_static_socket *br);
void		resume(char *buffer, struct s_static_socket *br);
void		set_append(char *buffer, struct s_static_socket *br);
char		*cwd_popen(struct s_static_socket *br);
char		*get_info(char *dest, char *buffer, ssize_t size);
ino_t		path_inode(int s_fd);
FILE		*popen(const char *command, const char *mode);
FILE		*popen_result(char *cmd);
#endif
