/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:18:50 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 18:20:50 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_env_entry(const char *key, const char *value)
{
	write(STDOUT_FILENO, key, ft_strlen(key));
	write(STDOUT_FILENO, "=", 1);
	write(STDOUT_FILENO, value, ft_strlen(value));
	write(STDOUT_FILENO, "\n", 1);
}

void	cmd_env(t_jobs *jobs)
{
	t_env	*environment;
	int		entry_index;

	environment = jobs->env;
	entry_index = 0;
	while (entry_index < environment->len)
	{
		print_env_entry(environment->key[entry_index],
			environment->value[entry_index]);
		entry_index++;
	}
	jobs->mshell->quest_mark = 0;
}
