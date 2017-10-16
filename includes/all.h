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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "libft.h"

# define FRAISE		1
# define bool		int
# define true		1
# define false		0
# define PATH_MAX	1024
# define BYTE		char

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
**	Program struct with all datas
*/
typedef struct		s_durex
{
	BYTE			*content;
	int				length;
	t_env			*env;
	char			*current_path;
}					t_durex;

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
void					infect_system(t_durex*);

/*
**	UTILS
*/
int						get_random(int low, int high);
int						get_file_length(char *path);

#endif
