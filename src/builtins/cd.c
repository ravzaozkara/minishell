/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:06:26 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 18:07:23 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	cmd_cd(t_jobs *job_context, char *directory_path)
{
	char		*resolved_path;
	const int	failure_status = 1;

	resolved_path = directory_path;
	if (!resolved_path)
	{
		resolved_path = env_getval(job_context->env, "HOME");
		if (!resolved_path)
		{
			job_context->mshell->quest_mark = failure_status;
			return (EXIT_FAILURE);
		}
	}
	if (chdir(resolved_path) == -1)
	{
		job_context->mshell->quest_mark = failure_status;
		perror("change_directory");
		return (EXIT_FAILURE);
	}
	job_context->mshell->quest_mark = 0;
	return (EXIT_SUCCESS);
}
