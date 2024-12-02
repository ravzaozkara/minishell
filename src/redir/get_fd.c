/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:14:51 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 20:36:37 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_file_descriptors(t_jobs *jobs, int fd, int last_fd,
		int indexes[5])
{
	if (fd == -1)
	{
		jobs->mshell->quest_mark = 1;
		return (-1);
	}
	if (fd != 1 && indexes[4] == 1)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), -1);
		last_fd = fd;
	}
	else if (fd != 0 && !indexes[4])
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), -1);
		last_fd = fd;
	}
	if (fd != 0 && fd != 1)
		close(fd);
	return (last_fd);
}

int	get_redirs(t_jobs *jobs, t_job *job)
{
	int	fd;
	int	indexes[5];
	int	last_fd;

	initialize_fd_indexes(indexes);
	if (!job->redir->files)
		return (1);
	last_fd = 1;
	indexes[3] = -1;
	while (job->redir->files[++indexes[3]])
	{
		fd = handle_redir(jobs, job, indexes);
		last_fd = handle_file_descriptors(jobs, fd, last_fd, indexes);
		if (last_fd == -1)
			return (-1);
	}
	return (last_fd);
}

int	open_output_file(t_jobs *jobs, t_job *job, char *filepath, int flags[5])
{
	int	fd;

	if (!filepath)
		return (-1);
	fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		jobs->mshell->quest_mark = 1;
		print_error(jobs, filepath, ": No such file or directory\n");
		return (-1);
	}
	if (access(filepath, W_OK))
	{
		jobs->mshell->quest_mark = 1;
		print_error(jobs, filepath, ": Permission denied\n");
		close(fd);
		return (-1);
	}
	if (check_redir_error(jobs, job, filepath, fd))
		return (close(fd), -1);
	job->redir->out_file = fd;
	flags[4] = 1;
	return (fd);
}
