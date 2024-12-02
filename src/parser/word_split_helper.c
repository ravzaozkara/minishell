/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:20:47 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 22:22:55 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	tokenize_init(t_quote_state *quote_status, t_parser_state *parser_state,
		char ***token_array)
{
	quote_status->in_single = false;
	quote_status->in_double = false;
	parser_state->quote_state = quote_status;
	parser_state->index = 0;
	parser_state->length = 0;
	*token_array = NULL;
}
