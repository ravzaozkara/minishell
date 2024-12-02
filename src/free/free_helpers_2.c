/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:51:49 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 20:51:51 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_cmd(t_mshell *mshell)
{
	t_job	*current;
	t_job	*next_job;

	if (mshell == NULL || mshell->jobs == NULL)
		return ;
	current = mshell->jobs->job_list;
	while (current != NULL)
	{
		next_job = current->next_job;
		free_job(current);
		current = next_job;
	}
	mshell->jobs->job_list = NULL;
}

void	free_array_ptr(char ***array)
{
	if (array == NULL || *array == NULL)
		return ;
	free_array(*array);
	*array = NULL;
}

void	free_env_struct(t_env *env)
{
	if (env == NULL)
		return ;
	free_array_ptr(&env->key);
	free_array_ptr(&env->value);
	free(env);
}
