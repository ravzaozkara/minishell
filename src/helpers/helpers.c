/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:57 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/20 21:33:58 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *env_find_value_const(t_env *env, const char *key)
{
    size_t key_length;
    int index;

	index = 0;
    if (!env || !key)
        return (NULL);
    key_length = ft_strlen(key);
	while (env->key[index])
	{
		if (ft_strlen(env->key[index]) == key_length && 
			!ft_strncmp(env->key[index], key, key_length))
			return (env->value[index]);
		index++;
	}
    return (NULL);
}

char *ft_strjoin_const(char *s1, const char *s2)
{
    char *result;
    size_t len1, len2;
    int i;

    if (!s1) {
        s1 = malloc(sizeof(char));
        if (!s1)
            return (NULL);
        s1[0] = '\0';
    }

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    
    result = malloc((len1 + len2 + 1) * sizeof(char));
    if (!result)
        return (NULL);

    for (i = 0; s1[i]; i++)
        result[i] = s1[i];
    for (int j = 0; s2[j]; j++)
        result[i + j] = s2[j];
        
    result[len1 + len2] = '\0';
    return (result);
}

int str_arr_len(char **array)
{
    int length;

    if (!array)
        return (0);
        
    for (length = 0; array[length]; length++);
    return (length);
}

char **str_arr_realloc(char **array, char *element)
{
    char **new_array;
    int index;
    int new_size;

    if (!array) {
        new_array = ft_calloc(2, sizeof(char *));
        if (!new_array)
            return (NULL);
            
        new_array[0] = ft_strdup(element);
        return (new_array);
    }

    new_size = str_arr_len(array) + 2;
    new_array = ft_calloc(new_size, sizeof(char *));
    if (!new_array)
        return (NULL);

    for (index = 0; array[index]; index++) {
        new_array[index] = ft_strdup(array[index]);
        if (!new_array[index]) {
            free_str_arr(new_array);
            return (NULL);
        }
    }

    new_array[index] = ft_strdup(element);
    free_str_arr(array);
    
    return (new_array);
}