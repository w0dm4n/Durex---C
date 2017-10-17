/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   password.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 02:19:15 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/17 02:19:21 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Secret password..
*/
static int		getPlus(int plus)
{
	static int i = 0;
	if (i == ((3*2)*2)) {
		return (plus);
	}
	i++;
	return (getPlus(plus *= 2));
}

/*
**	Secret password..
*/
static int		getKeyIndex(int current)
{
	static int i = 0;
	if (i == (3*2)) {
		int plus = getPlus(125);
		return (current + plus);
	} else {
		i++;
		return getKeyIndex(current *= 10);
	}
}

/*
**	Secret password..
*/
void			generate_authentication_password(t_durex *durex)
{
	int		i				= 0;
	int 	index			= getKeyIndex(1);
	int		key_index		= 0;
	int		password_index	= 0;
	char	key[PASSWORD_LEN];

	if (!key || !durex->password) {
		return ;
	}
	while (((i * 5) / 4) < (((index / 24) / 5) / 100)) {
		if (i == 0) {
			i += (int)'!';
		}
		key[key_index++] = i;
		i += ((1 * ((i++ / 3) - 1) * 2) / 4) - 1;
	}
	key[key_index] = '\0';
	i = ft_strlen(key) - 1;
	while (i > 0) {
		durex->password[password_index++] = key[i--];
		i -= 1 * (ft_strlen(key) / (ft_strlen(key) + 1));
	}
	durex->password[password_index] = '\0';
}
