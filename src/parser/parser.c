/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:30:19 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 20:30:19 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	initialize_job(t_job **job_node, char **token_array)
{
	t_job	*new_job;
	t_redir	*redir_struct;

	new_job = ft_calloc(1, sizeof(t_job));
	if (new_job == NULL)
	{
		free_array(token_array);
		return (EXIT_FAILURE);
	}
	(*job_node)->next_job = new_job;
	*job_node = new_job;
	new_job->redir = ft_calloc(1, sizeof(t_redir));
	if (new_job->redir == NULL)
	{
		free_array(token_array);
		return (EXIT_FAILURE);
	}
	redir_struct = new_job->redir;
	redir_struct->app_file = -1;
	redir_struct->in_file = -1;
	redir_struct->out_file = -1;
	redir_struct->last_in = 0;
	redir_struct->last_out = 0;
	return (EXIT_SUCCESS);
}

char	distribute(t_mshell *shell_instance, char **token_array)
{
	t_job	*current_job;
	char	redirect_flag;
	int		token_index;

	current_job = shell_instance->jobs->job_list;
	redirect_flag = -1;
	token_index = 0;
	shell_instance->jobs->len = 1;
	while (token_array[token_index] != NULL)
	{
		if (token_array[token_index][0] == '|')
		{
			shell_instance->jobs->len++;
			if (initialize_job(&current_job, token_array) != EXIT_SUCCESS)
				return (free_array(token_array), EXIT_FAILURE);
		}
		else if (handle_token(current_job, token_array[token_index],
				&redirect_flag))
			return (free_array(token_array), EXIT_FAILURE);
		token_index++;
	}
	return (free_array(token_array), EXIT_SUCCESS);
}

char	parse_cmd(t_jobs *jobs, char *input_line)
{
	char	**tokens;

	add_history(input_line);
	expand_cmd(jobs, &input_line);
	if (input_line[0] == '\0' || has_unclosed_quotes(jobs, input_line))
	{
		free(input_line);
		return (EXIT_FAILURE);
	}
	tokens = tokenize(input_line);
	free(input_line);
	if (tokens == NULL)
		return (EXIT_FAILURE);
	if (has_syntax_errors(jobs, tokens))
	{
		free_array(tokens);
		return (EXIT_FAILURE);
	}
	return (distribute(jobs->mshell, tokens));
}
