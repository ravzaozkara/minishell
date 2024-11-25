/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem <yunozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:40 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/21 18:14:49 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void built_in(t_job *job)
{
	if (!ft_strncmp(job->args[0], "pwd", 3) && ft_strlen(job->args[0]) == 3)
		job->built_in = true;
	else if (!ft_strncmp(job->args[0], "cd", 2) && ft_strlen(job->args[0]) == 2)
		job->built_in = true;
	else if (!ft_strncmp(job->args[0], "echo", 4) && ft_strlen(job->args[0]) == 4)
		job->built_in = true;
	else if (!ft_strncmp(job->args[0], "env", 3) && ft_strlen(job->args[0]) == 3)
		job->built_in = true;
	else if (!ft_strncmp(job->args[0], "exit", 4) && ft_strlen(job->args[0]) == 4)
		job->built_in = true;
	else if (!ft_strncmp(job->args[0], "unset", 5) && ft_strlen(job->args[0]) == 5)
		job->built_in = true;
	else if (!ft_strncmp(job->args[0], "export", 6) && ft_strlen(job->args[0]) == 6)
		job->built_in = true;
	else
		job->built_in = false;
}

static char ctrl_builtins_lh(t_jobs *jobs, t_job *job)
{
	if (!ft_strncmp(job->args[0], "echo", 4) && ft_strlen(job->args[0]) == 4)
		return (echo(jobs, job), jobs->mshell->quest_mark);
	else if (!ft_strncmp(job->args[0], "env", 3) && ft_strlen(job->args[0]) == 3)
		return (env(jobs), jobs->mshell->quest_mark);
	else if (!ft_strncmp(job->args[0], "exit", 4) && ft_strlen(job->args[0]) == 4)
		return (exit_d(jobs, job->args), jobs->mshell->quest_mark);
	else if (!ft_strncmp(job->args[0], "unset", 5) && ft_strlen(job->args[0]) == 5)
	{
		jobs->mshell->quest_mark = unset(&jobs->env, job->args);
		return (jobs->mshell->quest_mark);
	}
	else if (!ft_strncmp(job->args[0], "export", 6) && ft_strlen(job->args[0]) == 6)
		return (export(jobs, job->args));
	return (-1);
}

char ctrl_builtins(t_jobs *jobs, t_job *job)
{
	if (!ft_strncmp(job->args[0], "pwd", 3) && ft_strlen(job->args[0]) == 3)
	{
		jobs->mshell->quest_mark = pwd(jobs);
		return (jobs->mshell->quest_mark);
	}
	else if (!ft_strncmp(job->args[0], "cd", 2) && ft_strlen(job->args[0]) == 2)
	{
		jobs->mshell->quest_mark = cd(jobs, job->args[1]);
		return (jobs->mshell->quest_mark);
	}
	else if (ctrl_builtins_lh(jobs, job))
		return (-1);
	return (-1);
}
