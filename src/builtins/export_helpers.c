/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:59 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/24 17:09:32 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char update_env(t_env *env, char *key, char *value)
{
	size_t key_len;
	int i;

	key_len = ft_strlen(key);
	i = -1;
	while (env->key[++i])
	{
		if (!ft_strncmp(env->key[i], key, key_len) && key_len == ft_strlen(env->key[i]))
		{
			free(env->value[i]);
			env->value[i] = NULL;
			env->value[i] = ft_strdup(value);
			if (!env->value[i])
				return (-1);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
