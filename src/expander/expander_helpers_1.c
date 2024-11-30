/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:34 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/24 17:09:38 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void copy_env_value(char *value, char *result, int *positions)
{
    if (value) {
        size_t value_len = ft_strlen(value);
        ft_strlcpy(result + positions[1], value, value_len + 1);
        positions[1] += value_len;
    }
}

static void process_environment_variable(char *prompt, char *result, 
                                      t_jobs *jobs, int *positions)
{
    char *key;
    char *value;
    int var_end;

    var_end = positions[0];
    while (ft_isalnum(prompt[var_end]) || prompt[var_end] == '_')
        var_end++;

    key = ft_substr(prompt, positions[0], var_end - positions[0]);
    if (!key)
        return;

    value = env_find_value(jobs->env, key);
    free(key);
    
    copy_env_value(value, result, positions);
    positions[0] = var_end;
}

static void handle_exit_status(char *result, t_jobs *jobs, int *positions)
{
    char *status_str;

    status_str = ft_itoa(jobs->mshell->quest_mark);
    if (!status_str)
        return;

    copy_env_value(status_str, result, positions);
    free(status_str);
    positions[0]++;
}

static void handle_variable(char *prompt, char *result, 
                          t_jobs *jobs, int *positions)
{
    positions[0]++;

    if (!prompt[positions[0]] || prompt[positions[0]] == ' ' || 
        prompt[positions[0]] == '"' || prompt[positions[0]] == '\'') {
        result[positions[1]++] = '$';
        return;
    }

    if ((prompt[positions[0]] == '"') || 
        (prompt[positions[0]] == '\'' && prompt[positions[0] + 1] == '\'')) {
        positions[0] += 2;
        return;
    }

    if (prompt[positions[0]] == '?')
        handle_exit_status(result, jobs, positions);
    else if (ft_isalnum(prompt[positions[0]]) || prompt[positions[0]] == '_')
        process_environment_variable(prompt, result, jobs, positions);
    else
        result[positions[1]++] = '$';
}

static char *initialize_expansion(t_jobs *jobs, char *prompt, int **positions)
{
    char *result;
    t_quote_state initial_state = {false, false};

    if (!prompt)
        return (NULL);

    *positions = ft_calloc(3, sizeof(int));
    if (!*positions)
        return (NULL);

    (*positions)[2] = calc_len(jobs, prompt, initial_state);
    result = ft_calloc(1, (*positions)[2] + 2);
    
    if (!result) 
	{
        free(*positions);
        return (NULL);
    }

    return result;
}

char *expand_env_vars(t_jobs *jobs, char *prompt)
{
    t_quote_state quote_state = {false, false};
    char *result;
    int *positions;

    result = initialize_expansion(jobs, prompt, &positions);
    if (!result)
        return (NULL);

    while (prompt[positions[0]]) {
        update_quote_state(&quote_state, prompt[positions[0]]);

        if (prompt[positions[0]] == '$' && !quote_state.in_single) {
            if (!prompt[positions[0] + 1] || prompt[positions[0] + 1] == ' ') {
                result[positions[1]++] = prompt[positions[0]++];
                continue;
            }
            handle_variable(prompt, result, jobs, positions);
        } else {
            result[positions[1]++] = prompt[positions[0]++];
        }
    }

    result[positions[1]] = '\0';
    free(positions);
    return result;
}