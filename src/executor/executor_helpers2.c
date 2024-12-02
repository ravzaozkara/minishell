/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:31:13 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 21:19:32 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	run_cmd_error_ctrl(t_jobs *jobs, char *path)
{
	t_stat		file_info;
	const int	permission_error = 126;
	const int	not_found_error = 127;

	if (stat(path, &file_info) == -1)
		return ;
	if (S_ISDIR(file_info.st_mode))
	{
		jobs->mshell->quest_mark = 1;
		print_error(jobs, path, ": Is a directory\n");
		exit(permission_error);
	}
	if (!S_ISREG(file_info.st_mode))
	{
		jobs->mshell->quest_mark = 1;
		print_error(jobs, path, ": No such file or directory\n");
		exit(not_found_error);
	}
	if (access(path, R_OK) != 0)
	{
		jobs->mshell->quest_mark = 1;
		print_error(jobs, path, ": Permission denied\n");
		exit(permission_error);
	}
}

static char	*accessor(char *env_path, char *cmd)
{
	char	**path_directories;
	char	*full_path;
	char	*dir_with_slash;
	int		i;

	path_directories = ft_split(env_path, ':');
	if (!path_directories)
		return (NULL);
	i = 0;
	while (path_directories[i])
	{
		dir_with_slash = str_join(path_directories[i], "/");
		if (!dir_with_slash)
			continue ;
		full_path = ft_strjoin(dir_with_slash, cmd);
		free(dir_with_slash);
		if (!full_path)
			return (free_array(path_directories), NULL);
		if (access(full_path, X_OK) == 0)
			return (free_array(path_directories), full_path);
		free(full_path);
		i++;
	}
	return (free_array(path_directories), NULL);
}

static char	*get_exec_path(t_jobs *jobs, t_job *job, char *env_path)
{
	char	*executable_path;

	if (ft_strchr(job->args[0], '/'))
	{
		run_cmd_error_ctrl(jobs, job->args[0]);
		executable_path = ft_strdup(job->args[0]);
	}
	else
	{
		executable_path = accessor(env_path, job->args[0]);
	}
	if (!executable_path)
	{
		print_error(jobs, job->args[0], ": command not found\n");
		exit(127);
	}
	return (executable_path);
}

static char	handle_env_path_null(t_jobs *jobs, t_job *job, char **env)
{
	const int	no_path_error = 127;

	if (access(job->args[0], X_OK) == 0)
	{
		execve(job->args[0], job->args, env);
		exit(no_path_error);
	}
	jobs->mshell->quest_mark = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(job->args[0], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	exec_process(t_jobs *jobs, t_job *job)
{
	char		**environment;
	char		*executable_path;
	char		*path_var;
	const int	exec_failure = 127;

	path_var = env_getval(jobs->env, "PATH");
	environment = array_to_env(jobs->env);
	if (!path_var)
	{
		if (handle_env_path_null(jobs, job, environment))
			return ;
	}
	executable_path = get_exec_path(jobs, job, path_var);
	jobs->mshell->quest_mark = 0;
	execve(executable_path, job->args, environment);
	exit(exec_failure);
}
