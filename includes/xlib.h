#ifndef XLIB_H_
#define XLIB_H_

#include "include.h"

typedef struct addrinfo_
{
  int ai_flags;                 /* Input flags.  */
  int ai_family;                /* Protocol family for socket.  */
  int ai_socktype;              /* Socket type.  */
  int ai_protocol;              /* Protocol for socket.  */
  socklen_t ai_addrlen;         /* Length of socket address.  */
  struct sockaddr *ai_addr;     /* Socket address for socket.  */
  char *ai_canonname;           /* Canonical name for service location.  */
  struct addrinfo *ai_next;     /* Pointer to next in list.  */
}addrinfo;

void	set_sock_options(int s_fd);
void	reset_sock_options(int s_fd);
void	serv_timeout();
void	xfree(void *ptr);
void	*xmalloc(int var1);
void	xfclose(FILE *stream);
void	xpclose(FILE *stream);
void	xfpurge(FILE *stream);
void	sockstr(int sockfd, char *str);
int	pclose(FILE *stream);
int	xclose(int d);
int	kill(pid_t pid, int sig);
int	killpg(pid_t pid, int sig);
int	xkill(pid_t pid, int sig);
int	xdup2(int oldd, int newd);
int	xopen(const char *path, int flags);
int	xschdir(char *path, int sock);
int	xgetaddrinfo(const char *hostname, const char *servname,
		     const struct addrinfo *hints, struct addrinfo **res);
char	*xgetenv();
char	*xtgetstr(char *function, char *area);
ssize_t	xwrite(int d, const void *buf, size_t nbytes);
ssize_t	xrecv(int s, void *buf, size_t len, int flags);
ssize_t	xsend(int s, const void *msg, size_t len, int flags);
ssize_t	xsrecv(int s, void *buf, size_t len, int flags);
ssize_t	ping_content(void *buffer, ssize_t size);
ssize_t	xread(int d, void *buf, size_t nbytes);
ssize_t	xread_sun(int d, void *buf, size_t nbytes, int signal);
size_t	xfwrite(const void *ptr, size_t size,
		size_t nmemb, FILE *stream);
size_t	xfread(void *ptr, size_t size, size_t nmemb,
	       FILE *stream);
pid_t	xwait(int *statut);
pid_t	xfork(void);
void	bzero(void *b, size_t len);
#endif /*!XLIB_H_*/

