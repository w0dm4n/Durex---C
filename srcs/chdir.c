/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 02:57:44 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/18 02:57:50 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Get the above path from client pwd
*/
static char		*get_above_path(t_client *client)
{
	char		*above	= NULL;
	int			end		= ft_strlen(client->pwd) - 1;
	int			i		= 0;

	if (!(above = ft_strnew(PWD_CLIENT))) {
		return (NULL);
	}
	while (end) {
		if (client->pwd[end] == '/') {
			break;
		}
		end--;
	}
	while (i < end) {
		above[i] = client->pwd[i];
		i++;
	}
	if (ft_strlen(above) > 0) {
		return above;
	} else {
		ft_strdel(&above);
		return (ft_strdup("/"));
	}
}

/*
**	Set the client path
*/
static void		change_path(t_client *client, char *path, bool delete)
{
	ft_memset((char*)&client->pwd, 0, (PWD_CLIENT - 1));
	ft_strcat((char*)&client->pwd, path);
	if (delete) {
		ft_strdel(&path);
	}
}

/*
**	Handle pwd for client
*/
bool			handle_chdir(t_client *client, char *entry)
{
	char	*position	= ft_strstr(entry, "cd");
	char	*path		= NULL;
	char	in_path[PWD_CLIENT];
	bool	stderr		= true;

	if (position) {
		stderr = false;
		ft_memset((char*)&in_path, 0, (PWD_CLIENT - 1));
		char **args	= ft_strsplit(entry, ' ');
		if (args && ((path = args[1]) != NULL)) {
			if (path[0] == '/' && path_exist(path)) {
				change_path(client, path, false);
			} else if (!ft_strcmp(path, "..")) {
				change_path(client, get_above_path(client), true);
			} else {
				if (ft_strlen(client->pwd) > 1) {
					snprintf(in_path, (PWD_CLIENT -1), "%s/%s", client->pwd, path);
				} else {
					snprintf(in_path, (PWD_CLIENT -1), "%s%s", client->pwd, path);
				}
				if (path_exist(in_path)) {
					change_path(client, (char*)&in_path, false);
				}
			}
		}
		ft_free_array((void**)args);
	}
	chdir((char*)&client->pwd);
	return (stderr);
}
