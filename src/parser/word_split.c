/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:58:26 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 22:24:30 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	calculate_word_length_lh(t_parser_state *p_state, char *input)
{
	int		word_length;
	char	current_char;

	word_length = 0;
	while (input[p_state->index + word_length])
	{
		current_char = input[p_state->index + word_length];
		if (current_char == '\'' || current_char == '\"')
			toggle_quotes(p_state->quote_state, current_char);
		else if (!p_state->quote_state->in_single
			&& !p_state->quote_state->in_double && (current_char == ' '
				|| current_char == '<' || current_char == '>'
				|| current_char == '|'))
			break ;
		word_length++;
	}
	return (word_length);
}

static int	calculate_word_length(t_parser_state *p_state, char *input)
{
	if (input[p_state->index] == '<' || input[p_state->index] == '>'
		|| input[p_state->index] == '|')
	{
		if (input[p_state->index] != '|'
			&& input[p_state->index] == input[p_state->index + 1])
			return (2);
		else
			return (1);
	}
	return (calculate_word_length_lh(p_state, input));
}

static char	*extract_word(t_parser_state *p_state, char *input)
{
	char	*token;
	int		start_idx;

	while (input[p_state->index] && (input[p_state->index] == ' '
			|| input[p_state->index] == '\t' || input[p_state->index] == '\v'
			|| input[p_state->index] == '\f' || input[p_state->index] == '\r'))
		p_state->index++;
	if (!input[p_state->index])
		return (NULL);
	p_state->length = calculate_word_length(p_state, input);
	token = ft_calloc(p_state->length + 1, sizeof(char));
	if (!token)
		return (NULL);
	start_idx = p_state->index;
	p_state->index += p_state->length;
	ft_strlcpy(token, &input[start_idx], p_state->length + 1);
	return (token);
}

static char	*remove_quotes(char *token)
{
	char	*result;
	char	active_quote;
	int		idx;
	int		res_idx;

	active_quote = 0;
	idx = 0;
	res_idx = 0;
	result = ft_calloc(ft_strlen(token) + 1, sizeof(char));
	if (!result)
		return (NULL);
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
	return (result);
}

char	**tokenize(char *input)
{
	t_quote_state	quote_status;
	t_parser_state	parser_state;
	char			**token_array;
	char			*token;
	char			*clean_token;

	tokenize_init(&quote_status, &parser_state, &token_array);
	while (input[parser_state.index])
	{
		token = extract_word(&parser_state, input);
		if (!token)
			break ;
		clean_token = remove_quotes(token);
		free(token);
		if (clean_token)
		{
			token_array = arr_append(token_array, clean_token);
			free(clean_token);
			if (!token_array)
				return (NULL);
		}
		else
			return (free_array(token_array), NULL);
	}
	return (token_array);
}
