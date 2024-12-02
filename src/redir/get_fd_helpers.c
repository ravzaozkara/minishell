/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:20 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/20 21:34:21 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int open_output_file(t_jobs *jobs, t_job *job, char *filepath, int flags[5])
{
    int fd;

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
    {
        close(fd);
        return (-1);
    }
    job->redir->out_file = fd;
    flags[4] = 1;
    return (fd);
}

static int open_append_file(t_jobs *jobs, t_job *job, char *filepath, int flags[5])
{
    int fd;

    if (!filepath)
        return (-1);
    fd = open(filepath, O_CREAT | O_WRONLY | O_APPEND, 0644);
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
    {
        close(fd);
        return (-1);
    }
    job->redir->app_file = fd;
    flags[4] = 1;
    return (fd);
}

static int open_input_file(t_jobs *jobs, t_job *job, char *filepath, int flags[5])
{
    int fd;

    if (!filepath)
        return (-1);
    if (access(filepath, F_OK))
    {
        jobs->mshell->quest_mark = 1;
        print_error(jobs, filepath, ": No such file or directory\n");
        return (-1);
    }
    fd = open(filepath, O_RDONLY);
    if (fd == -1)
    {
        jobs->mshell->quest_mark = 1;
        print_error(jobs, filepath, ": Unable to open file\n");
        return (-1);
    }
    if (access(filepath, R_OK))
    {
        jobs->mshell->quest_mark = 1;
        print_error(jobs, filepath, ": Permission denied\n");
        close(fd);
        return (-1);
    }
    if (check_redir_error(jobs, job, filepath, fd))
    {
        close(fd);
        return (-1);
    }
    job->redir->in_file = fd;
    flags[4] = 0;
    return (fd);
}

static char verify_fd_match(char *redirect_str, char *filepath, int len1)
{
    int len2;

    if (!redirect_str)
        return (-1);
    len2 = ft_strlen(redirect_str);
    return (!ft_strncmp(filepath, redirect_str, len1) && len1 == len2);
}

int handle_redir(t_jobs *jobs, t_job *job, int flags[5])
{
    int fd;
    char *filepath;

    fd = 1;
    filepath = NULL;
    if (job->redir->files)
        filepath = job->redir->files[flags[3]];
    if (job->redir->out_f && verify_fd_match(job->redir->out_f[flags[0]], filepath, ft_strlen(filepath)) != -1)
        fd = open_output_file(jobs, job, job->redir->out_f[flags[0]++], flags);
    else if (job->redir->app_f && verify_fd_match(job->redir->app_f[flags[1]], filepath, ft_strlen(filepath)) != -1)
        fd = open_append_file(jobs, job, job->redir->app_f[flags[1]++], flags);
    else if (job->redir->in_f && verify_fd_match(job->redir->in_f[flags[2]], filepath, ft_strlen(filepath)) != -1)
        fd = open_input_file(jobs, job, job->redir->in_f[flags[2]++], flags);
    return (fd);
}