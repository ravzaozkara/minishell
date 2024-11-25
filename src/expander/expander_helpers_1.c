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

static void	expand_var_helper(char *value, char *result, int *temps)
{
	if (value)
	{
		ft_strlcpy(result + temps[1], value, ft_strlen(value) + 1);
		temps[1] += ft_strlen(value);
	}
}

static void	expand_variable(char *prompt, char *result, t_jobs *jobs,
		int *temps)
{
	char	*key;
	char	*value;
	int		start;

	start = temps[0];
	while (ft_isalnum(prompt[start]) || prompt[start] == '_')
		start++;
	key = ft_substr(prompt, temps[0], start - temps[0]);
	if (!key)
		return ;
	value = env_find_value(jobs->env, key);
	free(key);
	expand_var_helper(value, result, temps);
	temps[0] = start;
}

static void	process_quest_mark(char *result, t_jobs *jobs, int *temps)
{
	char	*value;

	value = ft_itoa(jobs->mshell->quest_mark);
	if (!value)
		return ;
	ft_strlcpy(result + temps[1], value, ft_strlen(value) + 1);
	temps[1] += ft_strlen(value);
	free(value);
	temps[0]++;
}

static void	process_variable(char *prompt, char *result, t_jobs *jobs,
		int *temps)
{
	temps[0]++;
    if (!prompt[temps[0]] || prompt[temps[0]] == ' ' || prompt[temps[0]] == '"' || prompt[temps[0]] == '\'')
    {
        result[temps[1]++] = '$';
        return;
    }
	if (prompt[temps[0]] == '"' || prompt[temps[0]] == '"'
		|| (prompt[temps[0]] == '\'' && prompt[temps[0] + 1] == '\''))
	{
        temps[0] += 2;
        return;
    }
	else if (prompt[temps[0]] == '?')
		process_quest_mark(result, jobs, temps);
	else if (ft_isalnum(prompt[temps[0]]) || prompt[temps[0]] == '_')
		expand_variable(prompt, result, jobs, temps);
	else
		result[temps[1]++] = '$';
}

static char *init_expand_vars(t_jobs *jobs, char *prompt, int **temps)
{
    char *result;
    t_quote_state state;

    if (!prompt)
        return (NULL);
    *temps = ft_calloc(3, sizeof(int));
    if (!*temps)
        return (NULL);
    state = (t_quote_state){false, false};
    (*temps)[2] = calc_len(jobs, prompt, state);
    result = ft_calloc(1, (*temps)[2] + 2);
    if (!result)
        return (free(*temps), NULL);
    return (result);
}

char *expand_env_vars(t_jobs *jobs, char *prompt)
{
    t_quote_state state;
    char *result;
    int *temps;

    result = init_expand_vars(jobs, prompt, &temps);
    if (!result)
        return (NULL);
    state = (t_quote_state){false, false};
    while (prompt[temps[0]])
    {
        update_quote_state(&state, prompt[temps[0]]);
        if (prompt[temps[0]] == '$' && !state.in_single)
        {
            if (!prompt[temps[0] + 1] || prompt[temps[0] + 1] == ' ') // $ işareti kontrolü eklendi
            {
                result[temps[1]++] = prompt[temps[0]++];
                continue;
            }
            process_variable(prompt, result, jobs, temps);
        }
        else
            result[temps[1]++] = prompt[temps[0]++];
    }
    result[temps[1]] = '\0';
    return (free(temps), result);
}
