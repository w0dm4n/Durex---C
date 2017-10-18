/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 21:43:52 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/17 21:43:57 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Print shell prompt
*/
static void		shell_prompt(t_client *client)
{
	char	prompt[] = "-> ";
	send(client->socket, (char*)&prompt, ft_strlen((char*)&prompt), 0);
}

/*
**	Execute user entry
*/
static void		execute_entry(t_client *client, char *buffer, bool err)
{
	pid_t	pid;
	int		out_pipe[2];
	char	output[ENTRY_BUFFER];
	int		return_status	= 0;
	int		res				= 0;
	char	*buffer_fork	= ft_strdup(buffer);

	if (!buffer_fork) {
		return;
	}
	pipe(out_pipe);
	pid = fork();
	if (pid == 0) {
		close(out_pipe[0]);
		fflush(stdout);
		fflush(stderr);
		dup2(out_pipe[1], STDOUT_FILENO);
		if (err) {
	  		dup2(out_pipe[1], STDERR_FILENO);
		}
		close(out_pipe[1]);
		system(buffer_fork);
		exit(0);
	} else if (pid > 0) {
		waitpid(pid, &return_status, 0);
		close(out_pipe[1]);
		if ((res = read(out_pipe[0], output, (ENTRY_BUFFER - 1))) > 0) {
			send(client->socket, (char*)&output, ft_strlen((char*)&output), 0);
			ft_memset((char*)&output, 0, (ENTRY_BUFFER - 1));
		}
		ft_strdel(&buffer_fork);
	}
}

/*
**	Shell client entries handler
*/
static void		handle_shell(t_client *client)
{
	char	buffer[CLIENT_BUFFER];
	int		res	= 0;

	ft_memset((char*)&buffer, 0, CLIENT_READ);
	shell_prompt(client);
	while (true)
	{
		if ((res = recv(client->socket, buffer, CLIENT_READ, 0)) > 0) {
			clear_buffer((char*)&buffer);
			if (!ft_strcmp(buffer, "exit")) {
				exit(0);
			}
			execute_entry(client, (char*)&buffer, handle_chdir(client, (char*)&buffer));
			ft_memset((char*)&buffer, 0, CLIENT_READ);
			shell_prompt(client);
		} else {
			exit (0);
		}
	}
}

/*
**	Fork the program to handle remote shell
*/
static void		init_shell(t_client *client)
{
	pid_t	pid				= fork();
	int		returnStatus	= 0;

	if (pid == 0) {
		handle_shell(client);
	} else {
    	waitpid(pid, &returnStatus, 0);
	}
}

/*
**	Init a shell on the remote server
*/
void			remote_shell(t_client *client)
{
	init_shell(client);
}
