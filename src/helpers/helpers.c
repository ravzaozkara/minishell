/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:45:48 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 20:48:57 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*env_getval(t_env *env_struct, const char *search_key)
{
	size_t	key_len;
	int		idx;

	idx = 0;
	if (!env_struct || !search_key)
		return (NULL);
	key_len = ft_strlen(search_key);
	while (env_struct->key[idx])
	{
		if (ft_strlen(env_struct->key[idx]) == key_len
			&& !ft_strncmp(env_struct->key[idx], search_key, key_len))
			return (env_struct->value[idx]);
		idx++;
	}
	return (NULL);
}

static char	*allocate_initial_string(void)
{
	char	*str1;

	str1 = malloc(sizeof(char));
	if (!str1)
		return (NULL);
	str1[0] = '\0';
	return (str1);
}

static char	*copy_strings(char *str1, const char *str2, size_t len1,
		size_t len2)
{
	char	*result;
	int		i;
	int		j;

	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (str1[++i])
		result[i] = str1[i];
	j = -1;
	while (str2[++j])
		result[i + j] = str2[j];
	result[len1 + len2] = '\0';
	return (result);
}

char	*str_join(char *str1, const char *str2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!str1)
	{
		str1 = allocate_initial_string();
		if (!str1)
			return (NULL);
	}
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	result = copy_strings(str1, str2, len1, len2);
	return (result);
}

int	arr_len(char **str_array)
{
	int	count;

	if (!str_array)
		return (0);
	count = 0;
	while (str_array[count])
		count++;
	return (count);
}
