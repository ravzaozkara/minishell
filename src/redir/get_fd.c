/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem <yunozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:22 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/21 21:51:06 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void initialize_fd_indexes(int indexes[4])
{
    indexes[0] = 0;
    indexes[1] = 0;
    indexes[2] = 0;
    indexes[4] = -1;
}

static int handle_file_descriptors(t_jobs *jobs, int fd, int last_fd, int indexes[5])
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

int get_fd(t_jobs *jobs, t_job *job)
{
    int fd;
    int indexes[5];
    int last_fd;

    initialize_fd_indexes(indexes);
    if (!job->redir->files)
        return (1);

    last_fd = 1;
    indexes[3] = -1;
    while (job->redir->files[++indexes[3]])
    {
        fd = get_fd_lh(jobs, job, indexes);
        last_fd = handle_file_descriptors(jobs,fd, last_fd, indexes);
        if (last_fd == -1)
            return (-1);
    }
    return (last_fd);
}
