/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 22:41:40 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/16 22:41:48 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Is the executable in a binary path from env values ?
*/
bool					is_in_binary_path(t_durex *durex)
{
	t_env		*path	= find_env_key(durex, "PATH");
	int			i		= 0;

	if (path) {
		char		**dirs	= ft_strsplit(path->value, ':');
		while (dirs[i]) {
			if (ft_strstr(durex->current_path, dirs[i++])) {
				return (true);
			}
		}
	}
	return (false);
}

/*
**	Get durex struct
*/
t_durex					*get_durex(char **env, int taste)
{
	t_durex		*durex = NULL;

	if (!(durex = (t_durex*)malloc(sizeof(struct s_durex)))) {
		return (NULL);
	}
	durex->env				= get_env(env);
	durex->current_path		= get_current_path();
	durex->password			= ft_strnew(PASSWORD_LEN);
	return (durex);
}

/*
**	Getting the current executable content
*/
void				get_durex_content(t_durex *durex)
{
	int		fd	= open(durex->current_path, O_RDONLY);
	if (fd > 0) {
		if ((durex->length = get_file_length(durex->current_path)) > 0) {
			if (!(durex->content = (char*)malloc(sizeof(char) * durex->length))) {
				return;
			}
			read(fd, durex->content, durex->length);
		}
		close(fd);
	}
}
