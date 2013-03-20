#ifndef __INCLUDE__
#define __INCLUDE__

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h> 
#include <sys/uio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define _XOPEN_SOURCE  600
#define USAGE_CLIENT "Usage: $>./client [host] [port]\n"
#define USAGE_SERVER "Usage: $>./serveur [-port 1024-65535] (Default: 1024) [-maxclient 0-128] (Default: 16)\n"
#endif
