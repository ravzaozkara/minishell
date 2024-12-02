/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:52:23 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 21:02:37 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	toggle_quotes(t_quote_state *state, char c)
{
	if (c == '\'' && !state->in_double)
		state->in_single = !state->in_single;
	else if (c == '\"' && !state->in_single)
		state->in_double = !state->in_double;
}

static int	measure_env_var_length(t_jobs *jobs, char *prompt, int *index)
{
	char	*key;
	char	*value;
	int		start_pos;
	int		value_len;

	start_pos = *index;
	while (ft_isalnum(prompt[*index]) || prompt[*index] == '_')
		(*index)++;
	key = ft_substr(prompt, start_pos, *index - start_pos);
	if (!key)
		return (0);
	value = env_find_value(jobs->env, key);
	value_len = 0;
	if (value)
		value_len = ft_strlen(value);
	return (free(key), value_len);
}

int	get_env_var_length(t_jobs *jobs, char *prompt, int *index)
{
	if (prompt[*index] == '"' || prompt[*index] == '\0'
		|| (prompt[*index] == '\'' && prompt[*index + 1] == '\''))
		return (0);
	return (measure_env_var_length(jobs, prompt, index));
}

int	calculate_exit_status_length(t_jobs *jobs, int *index)
{
	char	*status_str;
	int		length;

	status_str = ft_itoa(jobs->mshell->quest_mark);
	if (!status_str)
		return (0);
	length = ft_strlen(status_str);
	free(status_str);
	(*index)++;
	return (length);
}
