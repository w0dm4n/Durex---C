/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 22:53:48 by frmarinh          #+#    #+#             */
/*   Updated: 2017/10/16 22:54:07 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Alloc a new env chain
*/
static t_env			*alloc_env(char *key, char *value)
{
	t_env	*new_chain = NULL;

	if (!(new_chain = (t_env*)malloc(sizeof(struct s_env)))) {
		return (NULL);
	}
	new_chain->key = (key) ? ft_strdup(key) : NULL;
	new_chain->value = (value) ? ft_strdup(value) : NULL;
	new_chain->next = NULL;
	return (new_chain);
}

/*
**	Add a new chain to the list of env keys
*/
static t_env			*add_env(t_env *env, char *key, char *value)
{
	t_env	*new_chain	= alloc_env(key, value);
	t_env	*tmp_env	= env;
	if (new_chain && new_chain->key && new_chain->value) {
		if (tmp_env) {
			while (tmp_env->next)
				tmp_env = tmp_env->next;
			tmp_env->next = new_chain;
			return (env);
		} else {
			return (new_chain);
		}
	}
}

/*
**	Get all env vars
*/
t_env					*get_env(char **env_keys)
{
	t_env		*env = NULL;
	char		**tmp = NULL;
	int			i = 0;

	while (env_keys[i]) {
		if ((tmp = ft_strsplit(env_keys[i], '=')) != NULL) {
			if (tmp[0] && tmp[1]) {
				env = add_env(env, tmp[0], tmp[1]);
				ft_strdel(&tmp[0]);
				ft_strdel(&tmp[1]);
			}
		}
		i++;
	}
	return (env);
}

/*
**	Find env keys
*/
t_env				*find_env_key(t_durex *durex, char *key)
{
	t_env	*env = durex->env;

	while (env)
	{
		if (!ft_strcmp(env->key, key)) {
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}
