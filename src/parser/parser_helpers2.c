/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:18:59 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 20:44:44 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	check_redirection(char **redirection_list, char *cleaned_arg)
{
	int		list_length;
	size_t	arg_length;
	size_t	last_redir_length;

	if (!redirection_list)
		return (EXIT_SUCCESS);
	list_length = arr_len(redirection_list);
	arg_length = ft_strlen(cleaned_arg);
	last_redir_length = ft_strlen(redirection_list[list_length - 1]);
	if (last_redir_length == arg_length
		&& !ft_strncmp(redirection_list[list_length - 1], cleaned_arg,
			last_redir_length))
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	check_redir(t_redir *redir, char *arg)
{
	char		*trimmed_arg;
	const int	append_error = 1;

	trimmed_arg = ft_strtrim(arg, "\"");
	if (!trimmed_arg)
		return (append_error);
	if (check_redirection(redir->app_f, trimmed_arg)
		|| check_redirection(redir->in_f, trimmed_arg)
		|| check_redirection(redir->out_f, trimmed_arg)
		|| check_redirection(redir->eof, trimmed_arg))
	{
		free(trimmed_arg);
		return (append_error);
	}
	free(trimmed_arg);
	return (0);
}

bool	is_redirect_operator(char *arg)
{
	return ((arg[0] == '<' && !arg[1]) || (arg[0] == '>' && !arg[1])
		|| (arg[0] == '<' && arg[1] == arg[0] && !arg[2]) || (arg[0] == '>'
			&& arg[1] == arg[0] && !arg[2]));
}

char	append_to_files(t_job *job, char *arg)
{
	if (!job || !arg)
		return (EXIT_FAILURE);
	job->redir->files = arr_append(job->redir->files, arg);
	if (!job->redir->files)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	determine_redirect_type(char *arg, char *status)
{
	if (!arg || !arg[0])
	{
		*status = -1;
		return ;
	}
	if (arg[0] == '<')
	{
		if (!arg[1])
			*status = 0;
		else if (arg[1] == '<' && !arg[2])
			*status = 2;
		else
			*status = -1;
	}
	else if (arg[0] == '>')
	{
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
