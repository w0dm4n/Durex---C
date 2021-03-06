/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 02:58:10 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/17 05:09:41 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int i;
	char*tmp;
	int i2;
	int len_s1 = ft_strlen(s1);
	int total_len = len_s1 + ft_strlen(s2);
	i = -1;
	i2 = 0;
	if (!s1 || !s2)
		return (NULL);
	tmp = malloc(sizeof(char) * (total_len + 1));
	if (!tmp)
		return (NULL);
	while (i++ < total_len)
	{
		if (i < len_s1)
			tmp[i] = s1[i];
		else
		{
			tmp[i] = s2[i2];
			i2++;
		}
	}
	tmp[(i + i2)] = '\0';
	return (tmp);
}
