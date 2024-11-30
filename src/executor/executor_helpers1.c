/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:24 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/22 11:10:41 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int handle_external_command(t_jobs *jobs, t_job *job)
{
    job->pid = fork();
    if (job->pid == 0)
    {
        set_signal(CHILD);
        run_cmd(jobs, job);
        exit(jobs->mshell->quest_mark);
    }
    return (EXIT_SUCCESS);
}

char no_pipe(t_jobs *jobs, t_job *job)
{
    int file_descriptor;

    built_in(job);
    file_descriptor = get_fd(jobs, job);

    if (file_descriptor == -1)
        return (EXIT_FAILURE);

    if (job->built_in == false)
        return (handle_external_command(jobs, job));

    return (ctrl_builtins(jobs, job));
}



static int setup_pipe(int pipe_ends[2], t_job *job)
{
    if (pipe(pipe_ends) == -1)
    {
        perror("pipe");
        return (EXIT_FAILURE);
    }
    job->pid = fork();
    if (job->pid == -1)
    {
        close(pipe_ends[0]);
        close(pipe_ends[1]);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

static void handle_child_process(t_jobs *jobs, t_job *job, int pipe_ends[2])
{
    int file_descriptor;

    set_signal(CHILD);
    close(pipe_ends[0]);

    if (job->next_job && dup2(pipe_ends[1], STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(1);
    }
    close(pipe_ends[1]);

    if ((job->redir->in_f || job->redir->out_f || job->redir->app_f) &&
        (file_descriptor = get_fd(jobs, job)) == -1)
        exit(1);

    built_in(job);
    exit(job->built_in ? ctrl_builtins(jobs, job) :
         (run_cmd(jobs, job), jobs->mshell->quest_mark));
}

char pipe_handle(t_jobs *jobs, t_job *job)
{
    int pipe_ends[2];

    if (setup_pipe(pipe_ends, job) == EXIT_FAILURE)
        return (EXIT_FAILURE);

    if (job->pid == 0)
    {
        handle_child_process(jobs, job, pipe_ends);
        return (EXIT_SUCCESS);
    }

    close(pipe_ends[1]);
    if (dup2(pipe_ends[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        return (EXIT_FAILURE);
    }
    close(pipe_ends[0]);
    return (EXIT_SUCCESS);
}
