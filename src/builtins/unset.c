/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:07 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/20 21:33:08 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char unset(t_env **env, char **keys)
{
	char *value;
	int i;

	if (!*env)
		return (EXIT_FAILURE);
	if (!keys)
		return (EXIT_SUCCESS);
	i = -1;
	while (keys[++i])
	{
		value = env_find_value(*env, keys[i]);
		if (!value)
			continue;
		if (env_del_element(env, keys[i], value))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
