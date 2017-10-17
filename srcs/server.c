/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 01:28:22 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/17 01:28:28 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Alloc the server struct
*/
static t_server		*alloc_server(int listen_port)
{
	t_server		*server = NULL;
	if (!(server = (t_server*)malloc(sizeof(struct s_server)))) {
		return (NULL);
	}
	server->listen_port = listen_port;
	return (server);
}

/*
**	Wait for connections on the server
*/
static void			wait_clients(t_durex *durex)
{
	int 					fd		= 0;
	int						max_fd	= 0;
	struct sockaddr_in		in;
	socklen_t				length	= sizeof(in);

	while (true)
	{
		if ((fd = accept(durex->server->sock, (struct sockaddr*)&in, &length)) == -1)
			return;
		if (durex->clients < 3) {
			accept_client(fd, durex);
		} else {
			close(fd);
		}
	}
}

/*
**	Init the server for receiving clients
*/
void				init_server(int port, t_durex *durex)
{
	bool opt = true;
	if ((durex->server = alloc_server(port)) != NULL) {
		if ((durex->server->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
			return;
		durex->server->in.sin_family = AF_INET;
		durex->server->in.sin_addr.s_addr = INADDR_ANY;
		durex->server->in.sin_port = htons(port);
		setsockopt(durex->server->sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
		if ((bind(durex->server->sock, (struct sockaddr *)&durex->server->in, \
				sizeof(durex->server->in))) < 0)
			return ;
		if ((listen(durex->server->sock, 3)) == -1)
			return ;
		generate_authentication_password(durex);
		init_library(durex);
		init_daemon_service(durex);
		wait_clients(durex);
	}
}
