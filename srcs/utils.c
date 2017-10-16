/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 23:38:34 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/16 23:38:40 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int				get_random(int low, int high)
{
   return rand() % (high - low + 1) + low;
}

int				get_file_length(char *path)
{
	struct stat st;

	if ((stat(path, &st)) != -1) {
		return st.st_size;
	}
	return 0;
}
