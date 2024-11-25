/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:42 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/24 17:09:40 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void update_quote_state(t_quote_state *state, char c)
{
	if (c == '\'' && !state->in_double)
		state->in_single = !state->in_single;
	else if (c == '\"' && !state->in_single)
		state->in_double = !state->in_double;
}

static int handle_env_var(t_jobs *jobs, char *prompt, int *index)
{
	char *key;
	char *value;
	int start;
	int len;
	
	start = *index;
	while (ft_isalnum(prompt[*index]) || prompt[*index] == '_')
		(*index)++;
	key = ft_substr(prompt, start, *index - start);
	if (!key)
		return (0);
	value = env_find_value(jobs->env, key);
	len = value ? ft_strlen(value) : 0;
	free(key);
	return (len);
}

static int calc_env_var_len(t_jobs *jobs, char *prompt, int *index)
{
	if (prompt[*index] == '"' || prompt[*index] == '\0' ||
		(prompt[*index] == '\'' && prompt[*index + 1] == '\''))
		return (0);
	return (handle_env_var(jobs, prompt, index));
}

static int handle_quest_mark(t_jobs *jobs, int *index)
{
   char *temp;
	int len;

	temp = ft_itoa(jobs->mshell->quest_mark);
	if (!temp)
		return (0);
	len = ft_strlen(temp);
	free(temp);
	(*index)++;
	return (len);
}

static int calc_special_len(t_jobs *jobs, char *prompt, int *index)
{
	(*index)++;
	if (prompt[*index] == '?')
		return (handle_quest_mark(jobs, index));
	return (calc_env_var_len(jobs, prompt, index));
}

int calc_len(t_jobs *jobs, char *prompt, t_quote_state state)
{
	int len;
	int index;

	len = 0;
	index = 0;
	state.in_single = false;
	state.in_double = false;
	while (prompt[index])
	{
		update_quote_state(&state, prompt[index]);
		if (prompt[index] == '$' && !state.in_single)
		{
            len += calc_special_len(jobs, prompt, &index);
        }
		else
		{
            len++;
            index++;
        }
    }
    return (len + 1);
}
