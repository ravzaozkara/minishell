/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:02 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/20 21:34:03 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool is_redirect_operator(char *arg)
{
    return (arg[0] == '<' && !arg[1]) ||
           (arg[0] == '>' && !arg[1]) ||
           (arg[0] == '<' && arg[1] == arg[0] && !arg[2]) ||
           (arg[0] == '>' && arg[1] == arg[0] && !arg[2]);
}

static char append_to_files(t_job *job, char *arg)
{
    if (!job || !arg)
        return (EXIT_FAILURE);
        
    job->redir->files = str_arr_realloc(job->redir->files, arg);
    if (!job->redir->files)
        return (EXIT_FAILURE);
        
    return (EXIT_SUCCESS);
}

static void determine_redirect_type(char *arg, char *status)
{
    if (!arg || !arg[0]) {
        *status = -1;
        return;
    }

    if (arg[0] == '<') {
        if (!arg[1])
            *status = 0;
        else if (arg[1] == '<' && !arg[2])
            *status = 2;
        else 
            *status = -1;
    }
    else if (arg[0] == '>') {
        if (!arg[1])
            *status = 1;
        else if (arg[1] == '>' && !arg[2])
            *status = 3;
        else
            *status = -1;
    }
    else
        *status = -1;
}

static char handle_special_redirect(t_job *job, char *arg, char *status)
{
    if (*status == 2) {
        *status = -1;
        job->redir->last_in = 2;
        job->redir->eof = str_arr_realloc(job->redir->eof, arg);
        return (!job->redir->eof || append_to_files(job, arg)) ? 
               EXIT_FAILURE : EXIT_SUCCESS;
    }
    
    if (*status == 3) {
        *status = -1;
        job->redir->last_out = 2;
        job->redir->app_f = str_arr_realloc(job->redir->app_f, arg);
        return (!job->redir->app_f || append_to_files(job, arg)) ? 
               EXIT_FAILURE : EXIT_SUCCESS;
    }
    
    determine_redirect_type(arg, status);
    return (EXIT_SUCCESS);
}

static char handle_redirect(t_job *job, char *arg, char *status)
{
    if (*status == 0) {
        *status = -1;
        job->redir->last_in = 1;
        job->redir->in_f = str_arr_realloc(job->redir->in_f, arg);
        return (!job->redir->in_f || append_to_files(job, arg)) ? 
               EXIT_FAILURE : EXIT_SUCCESS;
    }
    
    if (*status == 1) {
        *status = -1;
        job->redir->last_out = 1;
        job->redir->out_f = str_arr_realloc(job->redir->out_f, arg);
        return (!job->redir->out_f || append_to_files(job, arg)) ? 
               EXIT_FAILURE : EXIT_SUCCESS;
    }
    
    return handle_special_redirect(job, arg, status);
}

char handle_distribute(t_job *job, char *arg, char *redir_status)
{
    char **current_args;
    char redirect_result;

    if (!job || !arg || !*arg)
        return (EXIT_FAILURE);

    current_args = job->args;
    redirect_result = handle_redirect(job, arg, redir_status);

    if (is_redirect_operator(arg))
        return (EXIT_SUCCESS);
        
    if (redirect_result == EXIT_FAILURE)
        return (EXIT_FAILURE);

    if (*redir_status == -1 && !ctrl_append(job->redir, arg)) {
        job->args = str_arr_realloc(current_args, arg);
        if (!job->args)
            return (free_str_arr(job->args), EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}
