/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:51:04 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 20:51:27 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_all_jobs(t_jobs *jobs)
{
	t_job	*current;
	t_job	*next_job;

	if (jobs == NULL)
		return ;
	if (jobs->job_list != NULL)
	{
		current = jobs->job_list;
		while (current != NULL)
		{
			next_job = current->next_job;
			free_job(current);
			current = next_job;
		}
	}
	if (jobs->env != NULL)
		free_env_struct(jobs->env);
	free(jobs);
}

void	free_job(t_job *job)
{
	if (job == NULL)
		return ;
	if (job->args != NULL)
		free_array(job->args);
	if (job->redir != NULL)
	{
		free_redirs(job->redir);
		job->redir = NULL;
	}
	free(job);
}

void	free_redirs(t_redir *redir)
{
	if (redir == NULL)
		return ;
	if (redir->files != NULL)
		free_array(redir->files);
	if (redir->eof != NULL)
		free_array(redir->eof);
	if (redir->in_f != NULL)
		free_array(redir->in_f);
	if (redir->out_f != NULL)
		free_array(redir->out_f);
	if (redir->app_f != NULL)
		free_array(redir->app_f);
	free(redir);
}

void	free_shell(t_mshell *mshell)
{
	if (mshell == NULL)
		return ;
	if (mshell->jobs != NULL)
		free_all_jobs(mshell->jobs);
	free(mshell);
}
