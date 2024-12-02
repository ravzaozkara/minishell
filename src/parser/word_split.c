/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:10 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/20 21:41:48 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int calculate_word_length(t_parser_state *p_state, char *input)
{
    int word_length = 0;
    char current_char;

    if (input[p_state->index] == '<' || input[p_state->index] == '>' || input[p_state->index] == '|')
    {
        if (input[p_state->index] != '|' && input[p_state->index] == input[p_state->index + 1])
            return 2;
        else
            return 1;
    }

    while (input[p_state->index + word_length])
    {
        current_char = input[p_state->index + word_length];

        if (current_char == '\'' || current_char == '\"')
            toggle_quotes(p_state->quote_state, current_char);
        else if (!p_state->quote_state->in_single && !p_state->quote_state->in_double &&
                 (current_char == ' ' || current_char == '<' || current_char == '>' || current_char == '|'))
            break;

        word_length++;
    }
    return word_length;
}

static char *extract_word(t_parser_state *p_state, char *input)
{
    char *token;
    int start_idx;

    // Skip whitespace characters
    while (input[p_state->index] && (input[p_state->index] == ' ' || input[p_state->index] == '\t' ||
                                     input[p_state->index] == '\v' || input[p_state->index] == '\f' ||
                                     input[p_state->index] == '\r'))
        p_state->index++;

    if (!input[p_state->index])
        return NULL;

    p_state->length = calculate_word_length(p_state, input);

    // Allocate memory for the token, including space for null terminator
    token = ft_calloc(p_state->length + 1, sizeof(char));
    if (!token)
        return NULL;

    start_idx = p_state->index;
    p_state->index += p_state->length;

    // Use ft_strlcpy to copy the word and ensure null-termination
    ft_strlcpy(token, &input[start_idx], p_state->length + 1);

    return token;
}


static char *remove_quotes(char *token)
{
    char *result;
    char active_quote = 0;
    int idx = 0, res_idx = 0;

    result = ft_calloc(ft_strlen(token) + 1, sizeof(char));
    if (!result)
        return NULL;

    while (token[idx])
    {
        if ((token[idx] == '\'' || token[idx] == '\"') && !active_quote)
            active_quote = token[idx];
        else if (token[idx] == active_quote)
            active_quote = 0;
        else
            result[res_idx++] = token[idx];
        idx++;
    }

    return result;
}

char **tokenize(char *input)
{
    t_quote_state quote_status = {false, false};
    t_parser_state parser_state = {&quote_status, 0, 0};
    char **token_array;
    char *token;
    char *clean_token;

	token_array = NULL;
    while (input[parser_state.index])
    {
        token = extract_word(&parser_state, input);
        if (!token)
            break;
        clean_token = remove_quotes(token);
        free(token);
        if (clean_token)
		{
			token_array = arr_append(token_array, clean_token);
			free(clean_token);
			if (!token_array)
				return NULL;
		}
		else
            return (free_array(token_array), NULL);
    }
    return token_array;
}
