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

static void get_fd_init(int indexes[4])
{
	indexes[0] = 0;
	indexes[1] = 0;
	indexes[2] = 0;
	indexes[4] = -1;
}

int get_fd(t_jobs *jobs, t_job *job)
{
    int fd;
    int indexes[5];

    get_fd_init(indexes);
    if (!job->redir->files)
        return (1);
    indexes[3] = -1;
    while (job->redir->files[++indexes[3]])
    {
        fd = get_fd_lh(jobs, job, indexes);
        if (fd == -1)
        {
            jobs->mshell->quest_mark = 1;
            return (-1);
        }
        
        if (fd != 1 && indexes[4] == 1)
            dup2(fd, STDOUT_FILENO);
        else if (fd != 0 && !indexes[4])
            dup2(fd, STDIN_FILENO);
            
        if (fd != 0 && fd != 1)
            close(fd);
    }
    return (fd);
}
