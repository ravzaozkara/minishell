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

void handle_sigint(int signal)
{
    if (signal == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        rl_on_new_line();
        rl_replace_line("", 0);
    }
}

static void main_signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

static void heredoc_signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        rl_replace_line("", 0);
        rl_on_new_line();
        exit(130);
    }
}

void set_signals(int context)
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

static char compare_strings(char *input, char *delimiter)
{
    int input_length;
    int delimiter_length;

    input_length = ft_strlen(input);
    delimiter_length = ft_strlen(delimiter);
    return (!ft_strncmp(input, delimiter, input_length) && input_length == delimiter_length);
}

static void handle_arguments(t_jobs *jobs, t_job *job, int pipe_fds[2])
{
    char *argument;
    char current_status;
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
        current_status = compare_strings(argument, job->redir->eof[index]);
        if (!current_status && argument && !job->redir->eof[index + 1])
            ft_putendl_fd(argument, pipe_fds[1]);
        if (current_status)
            index++;
        free(argument);
    }
}

static void execute_heredoc_child(t_jobs *jobs, t_job *job, int pipe_fds[2], char signal_handling)
{
    if (signal_handling)
        set_signals(HDOC);
    dup2(jobs->mshell->backup[0], STDIN_FILENO);
    handle_arguments(jobs, job, pipe_fds);
    close(pipe_fds[0]);
    close(pipe_fds[1]);
    exit(0);
}

char process_heredoc(t_jobs *jobs, t_job *job, char signal_handling)
{
    int status;
    int pipe_fds[2];

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

static void initialize_file_descriptors(int fd_indexes[4])
{
    fd_indexes[0] = 0;
    fd_indexes[1] = 0;
    fd_indexes[2] = 0;
    fd_indexes[3] = -1;
}

int manage_file_descriptors(t_jobs *jobs, t_job *job)
{
    int fd;
    int fd_indexes[5];
    int final_fd;

    initialize_file_descriptors(fd_indexes);
    if (!job->redir->files)
        return (1);

    final_fd = 1;
    fd_indexes[3] = -1;
    while (job->redir->files[++fd_indexes[3]])
    {
        fd = handle_redir(jobs, job, fd_indexes);
        if (fd == -1)
        {
            jobs->mshell->quest_mark = 1;
            return (-1);
        }
        
        if (fd != 1 && fd_indexes[4] == 1)
        {
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                close(fd);
                return (-1);
            }
            final_fd = fd; 
        }
        else if (fd != 0 && !fd_indexes[4])
        {
            if (dup2(fd, STDIN_FILENO) == -1)
            {
                close(fd);
                return (-1);
            }
            final_fd = fd;
        }
            
        if (fd != 0 && fd != 1)
            close(fd);
    }
    return (final_fd);
}