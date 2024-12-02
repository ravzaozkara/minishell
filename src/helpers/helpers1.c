/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:49:12 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 20:49:22 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**handle_empty_array(char *new_element)
{
	char	**resized_array;

	resized_array = ft_calloc(2, sizeof(char *));
	if (!resized_array)
		return (NULL);
	resized_array[0] = ft_strdup(new_element);
	return (resized_array);
}

char	**arr_append(char **str_array, char *new_element)
{
	char	**resized_array;
	int		idx;
	int		new_array_size;

	if (!str_array)
		return (handle_empty_array(new_element));
	new_array_size = arr_len(str_array) + 2;
	resized_array = ft_calloc(new_array_size, sizeof(char *));
	if (!resized_array)
		return (NULL);
	idx = 0;
	while (str_array[idx])
	{
		resized_array[idx] = ft_strdup(str_array[idx]);
		if (!resized_array[idx])
			return (free_array(resized_array), NULL);
		idx++;
	}
	resized_array[idx] = ft_strdup(new_element);
	return (free_array(str_array), resized_array);
}
