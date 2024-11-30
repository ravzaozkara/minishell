/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem <yunozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:40 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/21 18:34:02 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool is_special_char(const char *token)
{
    return (ft_strncmp(token, "|", 2) == 0 ||
            ft_strncmp(token, "<", 2) == 0 ||
            ft_strncmp(token, ">", 2) == 0 ||
            ft_strncmp(token, "<<", 3) == 0 ||
            ft_strncmp(token, ">>", 3) == 0);
}

static bool set_error_state(t_jobs *jobs, const char *error_message)
{
    jobs->mshell->quest_mark = 2;
    ft_putendl_fd((char *)error_message, 2);
    return true;
}

bool check_syntax_errors(t_jobs *jobs, char **tokens)
{
	int index;

	index = 0;
    while (tokens[index] != NULL)
    {
        if (ft_strncmp(tokens[index], "|", 2) == 0)
        {
            if (index == 0 || tokens[index + 1] == NULL)
                return set_error_state(jobs, "Syntax error near unexpected token '|'");
        }
        else if (is_special_char(tokens[index]))
        {
            if (tokens[index + 1] == NULL || (is_special_char(tokens[index + 1])))
                return set_error_state(jobs, "Syntax error near unexpected token");
        }
		index++;
    }
    return false;
}

bool check_unclosed_quotes(t_jobs *jobs, const char *input)
{
    char current_quote = 0;

    while (*input)
    {
        if ((*input == '\'' || *input == '"') && (current_quote == 0 || current_quote == *input))
        {
            current_quote = (current_quote == 0) ? *input : 0;
        }
        input++;
    }

    if (current_quote)
    {
        ft_putendl_fd("Syntax error: Unclosed quote", 2);
        jobs->mshell->quest_mark = 2;
        return true;
    }
    return false;
}