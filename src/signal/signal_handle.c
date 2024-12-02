/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:56:10 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 21:20:59 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	execute_heredoc_child(t_jobs *jobs, t_job *job, int pipe_fds[2],
		char signal_handling)
{
	if (signal_handling)
		set_signals(HDOC);
	dup2(jobs->mshell->backup[0], STDIN_FILENO);
	handle_arguments(jobs, job, pipe_fds);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	exit(0);
}

char	process_heredoc(t_jobs *jobs, t_job *job, char signal_handling)
{
	int	status;
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (EXIT_FAILURE);
	dup2(pipe_fds[0], STDIN_FILENO);
	job->pid = fork();
	if (job->pid == 0)
		execute_heredoc_child(jobs, job, pipe_fds, signal_handling);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(job->pid, &status, 0);
	if (signal_handling)
	{
		if (WIFEXITED(status))
			jobs->mshell->quest_mark = WEXITSTATUS(status);
	}
	return (EXIT_SUCCESS);
}

static int	process_file_descriptor(t_jobs *jobs, int fd,
		int fd_indexes[5], int *final_fd)
{
	if (fd == -1)
	{
		jobs->mshell->quest_mark = 1;
		return (-1);
	}
	if (fd != 1 && fd_indexes[4] == 1)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), -1);
		*final_fd = fd;
	}
	else if (fd != 0 && !fd_indexes[4])
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), -1);
		*final_fd = fd;
	}
	if (fd != 0 && fd != 1)
		close(fd);
	return (0);
}

int	manage_file_descriptors(t_jobs *jobs, t_job *job)
{
	int	fd;
	int	fd_indexes[5];
	int	final_fd;

	initialize_file_descriptors(fd_indexes);
	if (!job->redir->files)
		return (1);
	final_fd = 1;
	fd_indexes[3] = -1;
	while (job->redir->files[++fd_indexes[3]])
	{
		fd = handle_redir(jobs, job, fd_indexes);
		if (process_file_descriptor(jobs, fd, fd_indexes, &final_fd) == -1)
			return (-1);
	}
	return (final_fd);
}
