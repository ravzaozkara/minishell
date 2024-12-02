/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:24 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/22 10:27:02 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char calculate_state(char *arg, char *delimiter)
{
    int len_arg;
    int len_delim;

    len_arg = ft_strlen(arg);
    len_delim = ft_strlen(delimiter);
    return (!ft_strncmp(arg, delimiter, len_arg) && len_arg == len_delim);
}

static void process_arguments(t_jobs *jobs, t_job *job, int pipe_fd[2])
{
    char *argument;
    char current_state;
    int index;

    index = 0;
    while (job->redir->eof[index])
    {
        argument = readline("> ");
        if (!argument)
        {
            jobs->mshell->quest_mark = 130;
            exit(jobs->mshell->quest_mark);
        }
        current_state = calculate_state(argument, job->redir->eof[index]);
        if (!current_state && argument && !job->redir->eof[index + 1])
            ft_putendl_fd(argument, pipe_fd[1]);
        if (current_state)
            index++;
        free(argument);
    }
}

char handle_heredoc(t_jobs *jobs, t_job *job, char signal_state)
{
    int status;
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
        return (EXIT_FAILURE);
    dup2(pipe_fd[0], STDIN_FILENO);
    job->pid = fork();
    if (job->pid == 0)
    {
        if (signal_state)
            set_signals(HDOC);
        dup2(jobs->mshell->backup[0], STDIN_FILENO);
        process_arguments(jobs, job, pipe_fd);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        exit(0);
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(job->pid, &status, 0);
    if (signal_state && WIFEXITED(status))
        jobs->mshell->quest_mark = WEXITSTATUS(status);
    return (EXIT_SUCCESS);
}

static void initialize_fd_indexes(int indexes[4])
{
    indexes[0] = 0;
    indexes[1] = 0;
    indexes[2] = 0;
    indexes[4] = -1;
}

int determine_fd(t_jobs *jobs, t_job *job)
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
        fd = handle_redir(jobs, job, indexes);
        if (fd == -1)
        {
            jobs->mshell->quest_mark = 1;
            return (-1);
        }
        
        if (fd != 1 && indexes[4] == 1)
        {
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                close(fd);
                return (-1);
            }
            last_fd = fd; 
        }
        else if (fd != 0 && !indexes[4])
        {
            if (dup2(fd, STDIN_FILENO) == -1)
            {
                close(fd);
                return (-1);
            }
            last_fd = fd;
        }
            
        if (fd != 0 && fd != 1)
            close(fd);
    }
    return (last_fd);
}
