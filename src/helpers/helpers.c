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

char *env_getval(t_env *env_struct, const char *search_key)
{
    size_t key_len;
    int idx;

    idx = 0;
    if (!env_struct || !search_key)
        return (NULL);
    key_len = ft_strlen(search_key);
    while (env_struct->key[idx])
    {
        if (ft_strlen(env_struct->key[idx]) == key_len && 
            !ft_strncmp(env_struct->key[idx], search_key, key_len))
            return (env_struct->value[idx]);
        idx++;
    }
    return (NULL);
}

char *str_join(char *str1, const char *str2)
{
    char *concat_result;
    size_t str1_len, str2_len;
    int idx;

    if (!str1) {
        str1 = malloc(sizeof(char));
        if (!str1)
            return (NULL);
        str1[0] = '\0';
    }

    str1_len = ft_strlen(str1);
    str2_len = ft_strlen(str2);
    
    concat_result = malloc((str1_len + str2_len + 1) * sizeof(char));
    if (!concat_result)
        return (NULL);

    for (idx = 0; str1[idx]; idx++)
        concat_result[idx] = str1[idx];
    for (int j = 0; str2[j]; j++)
        concat_result[idx + j] = str2[j];
        
    concat_result[str1_len + str2_len] = '\0';
    return (concat_result);
}

int arr_len(char **str_array)
{
    int count;

    if (!str_array)
        return (0);
        
    for (count = 0; str_array[count]; count++);
    return (count);
}

char **arr_append(char **str_array, char *new_element)
{
    char **resized_array;
    int idx;
    int new_array_size;

    if (!str_array) {
        resized_array = ft_calloc(2, sizeof(char *));
        if (!resized_array)
            return (NULL);
            
        resized_array[0] = ft_strdup(new_element);
        return (resized_array);
    }

    new_array_size = arr_len(str_array) + 2;
    resized_array = ft_calloc(new_array_size, sizeof(char *));
    if (!resized_array)
        return (NULL);

    for (idx = 0; str_array[idx]; idx++) {
        resized_array[idx] = ft_strdup(str_array[idx]);
        if (!resized_array[idx]) {
            free_array(resized_array);
            return (NULL);
        }
    }

    resized_array[idx] = ft_strdup(new_element);
    free_array(str_array);
    
    return (resized_array);
}
