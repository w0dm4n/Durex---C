/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 23:38:34 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/16 23:38:40 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Return a random between low - high
*/
int				get_random(int low, int high)
{
   return rand() % (high - low + 1) + low;
}

/*
**	Return a file length
*/
int				get_file_length(char *path)
{
	struct stat st;

	if ((stat(path, &st)) != -1) {
		return st.st_size;
	}
	return 0;
}

/*
**	Check if the given path exist
*/
bool			path_exist(char *path)
{
	struct stat statStruct;
	stat(path, &statStruct);

	if (S_ISDIR(statStruct.st_mode)) {
	    return true;
	} else {
		return false;
	}
}

/*
**	Return the path of the current executable
*/
char			*get_current_path()
{
    char arg1[20];
    char exe_path[PATH_MAX + 1] = { 0 };

    sprintf(arg1, "/proc/%d/exe", getpid());
    readlink(arg1, exe_path, 1024);
    return ft_strdup(exe_path);
}

/*
**	Clear buffer from unwanted data
*/
bool			clear_buffer(char *buffer)
{
	if (buffer[(ft_strlen(buffer) - 1)] == '\n') {
		buffer[(ft_strlen(buffer) - 1)] = '\0';
		return true;
	}
	return false;
}
