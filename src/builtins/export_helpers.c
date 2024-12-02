/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:25:34 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 18:26:25 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	env_update(t_env *env, char *key, char *value)
{
	const int	env_update_error = -1;
	size_t		target_key_length;
	int			env_index;
	char		*new_value;

	if (!env || !key || !value)
		return (env_update_error);
	target_key_length = ft_strlen(key);
	env_index = 0;
	while (env->key[env_index])
	{
		if (ft_strlen(env->key[env_index]) == target_key_length
			&& !ft_strncmp(env->key[env_index], key, target_key_length))
		{
			new_value = ft_strdup(value);
			if (!new_value)
				return (env_update_error);
			free(env->value[env_index]);
			env->value[env_index] = new_value;
			return (EXIT_SUCCESS);
		}
		env_index++;
	}
	return (EXIT_FAILURE);
}
