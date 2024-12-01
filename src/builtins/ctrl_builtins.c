/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem <yunozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:40 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/21 18:14:49 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool is_command(const char *arg, const char *cmd, size_t len)
{
    return (!ft_strncmp(arg, cmd, len) && ft_strlen(arg) == len);
}

void built_in(t_job *job)
{
    const char *cmd = job->args[0];
    
    if (!cmd) {
        job->built_in = false;
        return;
    }
    
    job->built_in = (
        is_command(cmd, "pwd", 3) ||
        is_command(cmd, "cd", 2) ||
        is_command(cmd, "echo", 4) ||
        is_command(cmd, "env", 3) ||
        is_command(cmd, "exit", 4) ||
        is_command(cmd, "unset", 5) ||
        is_command(cmd, "export", 6)
    );
}

static char handle_basic_commands(t_jobs *jobs, t_job *job)
{
    const char *cmd = job->args[0];

    if (is_command(cmd, "echo", 4))
        return (echo(jobs, job), jobs->mshell->quest_mark);
    else if (is_command(cmd, "env", 3))
        return (env(jobs), jobs->mshell->quest_mark);
    else if (is_command(cmd, "exit", 4))
        return (exit_d(jobs, job->args), jobs->mshell->quest_mark);
    else if (is_command(cmd, "unset", 5))
        return ((jobs->mshell->quest_mark = unset(&jobs->env, job->args)));
    else if (is_command(cmd, "export", 6))
        return export(jobs, job->args);
    else
        return -1;
}

char ctrl_builtins(t_jobs *jobs, t_job *job)
{
    const char *cmd = job->args[0];
    
    if (is_command(cmd, "pwd", 3)) 
    {
        jobs->mshell->quest_mark = pwd(jobs);
        return jobs->mshell->quest_mark;
    }
    else if (is_command(cmd, "cd", 2)) 
    {
        jobs->mshell->quest_mark = cd(jobs, job->args[1]);
        return jobs->mshell->quest_mark;
    }
    return handle_basic_commands(jobs, job);
}
