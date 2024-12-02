/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:18:31 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 22:18:58 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	cmd_unset(t_env **env, char **keys)
{
	char	*env_value;
	int		key_index;

	if (!*env)
		return (EXIT_FAILURE);
	if (!keys)
		return (EXIT_SUCCESS);
	key_index = 0;
	while (keys[key_index])
	{
		key_index++;
		env_value = env_find_value(*env, keys[key_index]);
		if (!env_value)
			continue ;
		if (env_remove(env, keys[key_index], env_value))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
