/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 01:47:29 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/17 01:47:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Client thread
*/
static void				*client_thread(void *arg)
{
	t_client	*client	= (t_client*)arg;
	int			res		= 0;
	char		buffer[CLIENT_BUFFER];

	ft_memset(&buffer, 0, CLIENT_READ);
	if (authenticate_client(client)) {
		while (true)
		{
			if ((res = recv(client->socket, buffer, CLIENT_READ, 0)) > 0) {
				// still have to handle clients entries && remote shell
				ft_memset(&buffer, 0, CLIENT_READ);
			} else {
				client->durex->clients--;
				close(client->socket);
				return (NULL);
			}
		}
	}
	return (NULL);
}

/*
**	Alloc a new struct for the client
*/
static t_client			*alloc_client(SOCKET sock, t_durex *durex)
{
	t_client	*new_client = NULL;

	if (!(new_client = (t_client*)malloc(sizeof(struct s_client)))) {
		return (NULL);
	}
	new_client->socket = sock;
	new_client->durex = durex;
	return (new_client);
}

/*
**	Init the client thread
*/
static void				init_client_thread(SOCKET sock, t_durex *durex)
{
	t_client	*client = alloc_client(sock, durex);
	pthread_t	thread;
	if (client) {
		if (pthread_create(&thread, NULL, client_thread, client)) {
			return ;
    	}
	}
}

/*
**	Accept client connection
*/
void					accept_client(int fd, t_durex *durex)
{
	init_client_thread(fd, durex);
}
