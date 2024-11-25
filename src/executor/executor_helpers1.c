/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:24 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/22 11:10:41 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char no_pipe(t_jobs *jobs, t_job *job)
{
	int fd;

	built_in(job);
	fd = get_fd(jobs, job);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (job->built_in == false)
	{
		job->pid = fork();
		if (job->pid == 0)
		{
			set_signal(CHILD);
			run_cmd(jobs, job);
			exit(jobs->mshell->quest_mark);
		}
	}
	else
		return (ctrl_builtins(jobs, job));
	return (EXIT_SUCCESS);
}

static void pipe_handle_child(t_jobs *jobs, t_job *job, int pipe_fd[2])
{
	int fd;

	set_signal(CHILD);
	close(pipe_fd[0]);
	if (job->next_job)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
	}
	fd = 1;
	if (job->redir->in_f || job->redir->out_f || job->redir->app_f)
	{
		fd = get_fd(jobs, job);
		if (fd == -1)
			exit(1);
	}
	built_in(job);
	if (job->built_in == false)
		run_cmd(jobs, job);
	exit(ctrl_builtins(jobs, job));
}

char pipe_handle(t_jobs *jobs, t_job *job)
{
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return (EXIT_FAILURE);
    }

    job->pid = fork();
    if (job->pid == 0)
    {
        pipe_handle_child(jobs, job, pipe_fd);
    }
    
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    
    return (EXIT_SUCCESS);
}

static char *get_env_for_exec_lh(char *key)
{
	char *temp;
	char *arg;

	arg = ft_strdup(key);
	if (!arg)
		return (NULL);
	temp = arg;
	arg = ft_strjoin_const(arg, "=");
	free(temp);
	return (arg);
}

char **get_env_for_exec(t_env *env)
{
	char **rtrn;
	char *arg;
	char *temp;
	int i;

	rtrn = NULL;
	i = -1;
	while (++i < env->len)
	{
		arg = get_env_for_exec_lh(env->key[i]);
		if (!arg)
			return (NULL);
		temp = arg;
		arg = ft_strjoin_const(arg, env->value[i]);
		free(temp);
		if (!arg)
			return (NULL);
		rtrn = str_arr_realloc(rtrn, arg);
		free(arg);
	}
	return (rtrn);
}
