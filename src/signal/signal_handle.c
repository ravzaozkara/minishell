/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:32 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/20 21:34:33 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void handler_sigint(int sig)
{
    if (sig == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        rl_on_new_line();
        rl_replace_line("", 0);
    }
}

static void main_signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

static void heredoc_signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        rl_replace_line("", 0);
        rl_on_new_line();
        exit(130);
    }
}

void set_signal(int context)
{
    if (context == MAIN)
    {
        signal(SIGINT, &main_signal_handler);
        signal(SIGQUIT, SIG_IGN);
    }
    else if (context == CHILD)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
    }
    else if (context == HDOC)
    {
        signal(SIGINT, &heredoc_signal_handler);
        signal(SIGQUIT, SIG_IGN);
    }
    else
    {
        signal(SIGINT, SIG_IGN);
    }
}

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

static void heredoc_child_process(t_jobs *jobs, t_job *job, int pipe_fd[2], char signal_state)
{
    if (signal_state)
        set_signal(HDOC);
    dup2(jobs->mshell->backup[0], STDIN_FILENO);
    process_arguments(jobs, job, pipe_fd);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    exit(0);
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
        heredoc_child_process(jobs, job, pipe_fd, signal_state);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(job->pid, &status, 0);
    if (signal_state)
    {
        if (WIFEXITED(status))
            jobs->mshell->quest_mark = WEXITSTATUS(status);
    }
    return (EXIT_SUCCESS);
}

static void initialize_fd_indexes(int indexes[4])
{
    indexes[0] = 0;
    indexes[1] = 0;
    indexes[2] = 0;
    indexes[4] = -1;
}

int manage_fd(t_jobs *jobs, t_job *job)
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
