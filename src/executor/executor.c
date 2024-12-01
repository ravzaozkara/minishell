/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem <yunozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:29 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/21 21:07:34 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void wait_child(t_mshell *mshell)
{
    t_job *current;
    int process_status;
    int final_status;

    current = mshell->jobs->job_list;
    if (mshell->jobs->len == 1 && current->built_in == true)
        return;
    final_status = 0;
    while (current)
    {
        signal(SIGINT, &handler_sigint);
        if (current->pid <= 0)
            continue;
            
        if (waitpid(current->pid, &process_status, 0) > 0)
        {
            final_status = WIFEXITED(process_status) ? 
                          WEXITSTATUS(process_status) : 
                          (WIFSIGNALED(process_status) ? 128 + WTERMSIG(process_status) : 0);
        }
        current = current->next_job;
    }
    mshell->quest_mark = (mshell->quest_mark == 130) ? 
                        mshell->quest_mark : final_status;
}

static int executer_while(t_mshell *mshell, t_job *current_job)
{
    const int is_single_job = mshell->jobs->len == 1;
    
    if (is_single_job)
    {
        if (current_job->redir->eof && 
            heredoc(mshell->jobs, current_job, 1))
            return (0);
        else if (no_pipe(mshell->jobs, current_job))
            return (0);
    }
    else
    {
        if (current_job->redir->eof && 
            heredoc(mshell->jobs, current_job, 0))
            return (0);
        else if (mshell->quest_mark == 130 || 
            pipe_handle(mshell->jobs, current_job))
            return (0);
        mshell->quest_mark = 0;
    }
    return (1);
}

void get_backup(t_mshell *mshell)
{
    if (dup2(mshell->backup[0], STDIN_FILENO) != -1)
        close(mshell->backup[0]);
    if (dup2(mshell->backup[1], STDOUT_FILENO) != -1)
        close(mshell->backup[1]);
}

char executor(t_mshell *mshell)
{
    t_job *current_job;
    int execution_status;

    execution_status = 1;
    mshell->backup[0] = dup(STDIN_FILENO);
    mshell->backup[1] = dup(STDOUT_FILENO);
    
    current_job = mshell->jobs->job_list;
	while (current_job && execution_status == 1)
	{
		execution_status = executer_while(mshell, current_job);
		current_job = current_job->next_job;
	}
    get_backup(mshell);
    if (execution_status)
        wait_child(mshell);
    return (EXIT_SUCCESS);
}