/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:08:22 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 18:16:51 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_command(const char *arg, const char *cmd, size_t len)
{
	return (!ft_strncmp(arg, cmd, len) && ft_strlen(arg) == len);
}

static char	handle_helper(t_jobs *jobs, t_job *job, const char *cmd)
{
	if (is_command(cmd, "env", 3))
	{
		cmd_env(jobs);
		return (jobs->mshell->quest_mark);
	}
	else if (is_command(cmd, "exit", 4))
	{
		cmd_exit(jobs, job->args);
		return (jobs->mshell->quest_mark);
	}
	else if (is_command(cmd, "unset", 5))
	{
		jobs->mshell->quest_mark = cmd_unset(&jobs->env, job->args);
		return (jobs->mshell->quest_mark);
	}
	else if (is_command(cmd, "export", 6))
	{
		return (export(jobs, job->args));
	}
	else
	{
		return (-1);
	}
}

static char	handle_basic_commands(t_jobs *jobs, t_job *job)
{
	const char	*cmd = job->args[0];

	if (is_command(cmd, "pwd", 3))
	{
		jobs->mshell->quest_mark = cmd_pwd(jobs);
		return (jobs->mshell->quest_mark);
	}
	else if (is_command(cmd, "cd", 2))
	{
		jobs->mshell->quest_mark = cmd_cd(jobs, job->args[1]);
		return (jobs->mshell->quest_mark);
	}
	else if (is_command(cmd, "echo", 4))
	{
		cmd_echo(jobs, job);
		return (jobs->mshell->quest_mark);
	}
	return (handle_helper(jobs, job, cmd));
}

void	check_builtin(t_job *job)
{
	const char	*cmd = job->args[0];

	if (!cmd)
	{
		job->built_in = false;
		return ;
	}
	job->built_in = (is_command(cmd, "pwd", 3) || is_command(cmd, "cd", 2)
			|| is_command(cmd, "echo", 4) || is_command(cmd, "env", 3)
			|| is_command(cmd, "exit", 4) || is_command(cmd, "unset", 5)
			|| is_command(cmd, "export", 6));
}

char	exec_builtin(t_jobs *jobs, t_job *job)
{
	return (handle_basic_commands(jobs, job));
}
