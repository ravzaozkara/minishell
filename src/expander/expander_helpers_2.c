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

void toggle_quotes(t_quote_state *state, char c)
{
    if (c == '\'' && !state->in_double)
        state->in_single = !state->in_single;
    else if (c == '\"' && !state->in_single)
        state->in_double = !state->in_double;
}

static int measure_env_var_length(t_jobs *jobs, char *prompt, int *index)
{
    char *key;
    char *value;
    int start_pos;
    int value_len;
    
    start_pos = *index;
    while (ft_isalnum(prompt[*index]) || prompt[*index] == '_')
        (*index)++;

    key = ft_substr(prompt, start_pos, *index - start_pos);
    if (!key)
        return (0);

    value = env_find_value(jobs->env, key);
    value_len = value ? ft_strlen(value) : 0;
    
    free(key);
    return (value_len);
}

static int get_env_var_length(t_jobs *jobs, char *prompt, int *index)
{
    if (prompt[*index] == '"' || prompt[*index] == '\0' ||
        (prompt[*index] == '\'' && prompt[*index + 1] == '\''))
        return (0);
        
    return (measure_env_var_length(jobs, prompt, index));
}

static int calculate_exit_status_length(t_jobs *jobs, int *index)
{
    char *status_str;
    int length;

    status_str = ft_itoa(jobs->mshell->quest_mark);
    if (!status_str)
        return (0);
        
    length = ft_strlen(status_str);
    free(status_str);
    (*index)++;
    
    return (length);
}

static int handle_special_character(t_jobs *jobs, char *prompt, int *index)
{
    (*index)++;
    
    if (prompt[*index] == '?')
        return (calculate_exit_status_length(jobs, index));
        
    return (get_env_var_length(jobs, prompt, index));
}

int calc_expanded_len(t_jobs *jobs, char *prompt, t_quote_state state)
{
    int total_length;
    int position;

    total_length = 0;
    position = 0;
    
    state.in_single = false;
    state.in_double = false;
    
    while (prompt[position]) {
        toggle_quotes(&state, prompt[position]);
        
        if (prompt[position] == '$' && !state.in_single) {
            total_length += handle_special_character(jobs, prompt, &position);
        } else {
            total_length++;
            position++;
        }
    }
    
    return (total_length + 1);
}