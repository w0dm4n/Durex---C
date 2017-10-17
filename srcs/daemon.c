/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 01:20:39 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/17 01:20:43 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void			init_daemon_default()
{
	/*close(0);
	close(1);
	close(2);*/

	chdir("/");
}

void				init_daemon(t_durex *durex)
{
	pid_t	pid = fork();
	if (pid == 0) {
		int sid = setsid();
		if (sid > 0) {
			pid_t new_pid = fork();
			if (new_pid == 0) {
				init_daemon_default();
				init_server(4242, durex);
			} else if (new_pid > 0) {
				exit(0);
			}
		}
	} else if (pid > 0) {
		exit (0);
	}
}
