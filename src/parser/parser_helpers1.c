/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:19:09 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 21:08:46 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	handle_heredoc_parser(t_job *job, char *arg, char *status)
{
	*status = -1;
	job->redir->last_in = 2;
	job->redir->eof = arr_append(job->redir->eof, arg);
	if (!job->redir->eof || append_to_files(job, arg))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	handle_special_redirect(t_job *job, char *arg, char *status)
{
	if (*status == 2)
		return (handle_heredoc_parser(job, arg, status));
	if (*status == 3)
	{
		*status = -1;
		job->redir->last_out = 2;
		job->redir->app_f = arr_append(job->redir->app_f, arg);
		if (!job->redir->app_f || append_to_files(job, arg))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	determine_redirect_type(arg, status);
	return (EXIT_SUCCESS);
}

static char	handle_input_redirect(t_job *job, char *arg, char *status)
{
	*status = -1;
	job->redir->last_in = 1;
	job->redir->in_f = arr_append(job->redir->in_f, arg);
	if (!job->redir->in_f || append_to_files(job, arg))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	handle_redirect(t_job *job, char *arg, char *status)
{
	if (*status == 0)
		return (handle_input_redirect(job, arg, status));
	if (*status == 1)
	{
		*status = -1;
		job->redir->last_out = 1;
		job->redir->out_f = arr_append(job->redir->out_f, arg);
		if (!job->redir->out_f || append_to_files(job, arg))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (handle_special_redirect(job, arg, status));
}

char	handle_token(t_job *job, char *arg, char *redir_status)
{
	char	**current_args;
	char	redirect_result;

	if (!job || !arg || !*arg)
		return (EXIT_FAILURE);
	current_args = job->args;
	redirect_result = handle_redirect(job, arg, redir_status);
	if (is_redirect_operator(arg))
		return (EXIT_SUCCESS);
	if (redirect_result == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (*redir_status == -1 && !check_redir(job->redir, arg))
	{
		job->args = arr_append(current_args, arg);
		if (!job->args)
			return (free_array(job->args), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
