/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:54:44 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 20:58:47 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	process_special_char(char *prompt, char *result, t_jobs *jobs,
		int *positions)
{
	if (!prompt[positions[0] + 1] || prompt[positions[0] + 1] == ' ')
	{
		result[positions[1]++] = prompt[positions[0]++];
	}
	else
		handle_variable(prompt, result, jobs, positions);
}

char	*expand_vars(t_jobs *jobs, char *prompt)
{
	t_quote_state	quote_state;
	char			*result;
	int				*positions;

	quote_state.in_single = false;
	quote_state.in_double = false;
	result = initialize_expansion(jobs, prompt, &positions);
	if (!result)
		return (NULL);
	while (prompt[positions[0]])
	{
		toggle_quotes(&quote_state, prompt[positions[0]]);
		if (prompt[positions[0]] == '$' && !quote_state.in_single)
			process_special_char(prompt, result, jobs, positions);
		else
			result[positions[1]++] = prompt[positions[0]++];
	}
	result[positions[1]] = '\0';
	return (free(positions), result);
}

static int	handle_special_character(t_jobs *jobs, char *prompt, int *index)
{
	(*index)++;
	if (prompt[*index] == '?')
		return (calculate_exit_status_length(jobs, index));
	return (get_env_var_length(jobs, prompt, index));
}

int	calc_expanded_len(t_jobs *jobs, char *prompt, t_quote_state state)
{
	int	total_length;
	int	position;

	total_length = 0;
	position = 0;
	state.in_single = false;
	state.in_double = false;
	while (prompt[position])
	{
		toggle_quotes(&state, prompt[position]);
		if (prompt[position] == '$' && !state.in_single)
			total_length += handle_special_character(jobs, prompt, &position);
		else
		{
			total_length++;
			position++;
		}
	}
	return (total_length + 1);
}
