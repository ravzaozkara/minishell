/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doaltin <doaltin@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:49 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/29 23:02:28 by doaltin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int validate_n_flag(char *arg)
{
    int index;

    if (!arg || arg[0] != '-' || arg[1] != 'n')
        return (0);
        
    index = 2;
    while (arg[index]) {
        if (arg[index] != 'n')
            return (0);
        index++;
    }
    
    return (1);
}

static void print_argument(char *arg, bool has_next_arg)
{
    if (!arg[0])
        ft_putchar_fd('\0', STDOUT_FILENO);
    else
        ft_putstr_fd(arg, STDOUT_FILENO);
        
    if (has_next_arg)
        ft_putchar_fd(' ', STDOUT_FILENO);
}

void echo(t_jobs *jobs, t_job *job)
{
    int arg_index;
    bool print_newline;
    
    print_newline = true;
    arg_index = 1;
    
    /* Process -n flags */
    while (job->args[arg_index] && validate_n_flag(job->args[arg_index])) {
        print_newline = false;
        arg_index++;
    }

    /* Print arguments */
    while (job->args[arg_index]) {
        print_argument(job->args[arg_index], 
                      job->args[arg_index + 1] != NULL);
        arg_index++;
    }

    if (print_newline)
        ft_putchar_fd('\n', STDOUT_FILENO);
        
    jobs->mshell->quest_mark = 0;
}