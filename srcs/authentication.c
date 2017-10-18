/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authentication.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 02:10:07 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/17 02:10:16 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Used to authenticate the client with an hidden password
*/
bool	authenticate_client(t_client *client)
{
	char buffer[CLIENT_BUFFER];
	char welcome_message[]	= "Please enter the password to access to the daemon:\n";
	char success_message[]	= "Password correct ! Welcome master, please use help to see available commands\n";
	char error_message[]	= "Incorrect password, please try again\n";

	while (true) {
		ft_memset(&buffer, 0, CLIENT_READ);
		send(client->socket, (char*)&welcome_message, ft_strlen((char*)&welcome_message), 0);
		int res = recv(client->socket, buffer, CLIENT_READ, 0);
		if (res > 0) {
			clear_buffer((char*)&buffer);
			if (!ft_strcmp(buffer, client->durex->password)) {
				send(client->socket, (char*)&success_message, ft_strlen((char*)&success_message), 0);
				return true;
			} else {
				send(client->socket, (char*)&error_message, ft_strlen((char*)&error_message), 0);
			}
		} else {
			client->durex->clients--;
			close(client->socket);
			return false;
		}
	}
	return false;
}
