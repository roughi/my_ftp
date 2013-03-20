NAME_CLIENT	=	client

NAME_SERVER	=	serveur

SRC_COMMON	=	./lib/xmalloc.c \
			./lib/xwrite.c \
			./lib/xfree.c \
			./lib/xread.c \
			./lib/xkill.c \
			./lib/xwait.c \
			./lib/xconnect.c \
			./lib/xgethostbyname.c \
			./lib/ping.c \
			./lib/xfork.c \
			./lib/xclose.c \
			./lib/my_putstr.c \
			./lib/my_put_nbr.c \
			./lib/my_putchar.c \
			./lib/my_getnbr.c \
			./lib/my_strcpy.c \
			./lib/my_getstr.c \
			./lib/my_strlen.c \
			./lib/set_sock_options.c \
			./lib/verify_option.c \
			./lib/put_time.c \
			./lib/my_accept.c

SRC_CLIENT	=  	./lib/swrite.c \
			./lib/xselect.c \
			./src_client/main.c \
			./src_client/welcome.c \
			./src_client/change_directory.c \
			./src_client/serv_timeout.c \
			./src_client/get_auth.c \
			./src_client/show_pwd.c \
			./src_client/check_op.c \
			./src_client/make_dir.c \
			./src_client/rm_file.c \
			./src_client/chmod.c \
			./src_client/mv_file.c \
			./src_client/lcd.c \
			./src_client/is_ip.c \
			./src_client/static_info.c \
			./src_client/get_dataconnection.c \
			./src_client/list_file.c \
			./src_client/get_file.c \
			./src_client/get_file_suite.c \
			./src_client/put_file.c \
			./src_client/put_file_suite.c \
			./src_client/accept_client.c \
			./src_client/get_info.c \
			./src_client/is_only_num.c \
			./src_client/get_hostname.c \
			./src_client/init_socket.c \
			./src_client/write_usage.c

SRC_SERVER	=	./lib/get_ip.c \
			./lib/s_swrite.c \
			./lib/xfread.c \
			./src_server/xschdir.c \
			./src_server/main.c \
			./src_server/serv_timeout.c \
			./src_server/welcome.c \
			./src_server/write_usage.c \
			./src_server/rmd.c \
			./src_server/rmd_suite.c \
			./src_server/mkdir.c \
			./src_server/chmod.c \
			./src_server/retrieve_file.c \
			./src_server/retrieve_file_suite.c \
			./src_server/site_cmd.c \
			./src_server/limit_usage.c \
			./src_server/close_passive.c \
			./src_server/parse_arg_param.c \
			./src_server/init_client.c \
			./src_server/abor.c \
			./src_server/open_dataconnection.c \
			./src_server/resume.c \
			./src_server/rename_from.c \
			./src_server/rename_from_suite.c \
			./src_server/store_file.c \
			./src_server/store_file_suite.c \
			./src_server/check_user.c \
			./src_server/authentification.c \
			./src_server/change_directory.c \
			./src_server/change_directory_suite.c \
			./src_server/relative_cmd.c \
			./src_server/popen_result.c \
			./src_server/passive_list.c \
			./src_server/get_passive.c \
			./src_server/static_info.c \
			./src_server/read_dir.c \
			./src_server/accept_client.c \
			./src_server/talk_client.c \
			./src_server/signal.c \
			./src_server/init_socket.c \
			./src_server/init_listen.c

OBJ_CLIENT	= 	$(SRC_CLIENT:.c=.o) $(SRC_COMMON:.c=.o)

OBJ_SERVER	= 	$(SRC_SERVER:.c=.o) $(SRC_COMMON:.c=.o)

CC              =       gcc

RM		= 	rm -f

CFLAGS		= 	-W -Wall -Werror -g -I./includes

all		:	$(NAME_CLIENT) $(NAME_SERVER)

.c.o		:
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

$(NAME_CLIENT)	:	$(OBJ_CLIENT)
			$(CC) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LIB)

$(NAME_SERVER)	:	$(OBJ_SERVER)
			$(CC) -o $(NAME_SERVER) $(OBJ_SERVER) $(LIB)

# server		:	clean $(NAME_SERVER) clean

# client		:	
# 			gcc -I./includes $(SRC_CLIENT) $(SRC_COMMON) -o $(NAME_CLIENT)

pass		:	
			rm -rf ./ftp_data
			mkdir -p ./ftp_data
			touch ./ftp_data/users.conf

clean		:
			$(RM) $(OBJ_CLIENT) $(OBJ_SERVER)
			$(RM) *~
			$(RM) */*~

fclean		:	clean
			rm -f $(NAME_CLIENT) $(NAME_SERVER)

re		: 	fclean all

.PHONY		:	all re clean fclean
