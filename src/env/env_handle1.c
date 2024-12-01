/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:18 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/22 13:35:51 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char env_del_element(t_env **env, char *key, char *value)
{
    t_env *environment;
    size_t target_length;
    size_t current_length;
    int index;

    if (!key || !value)
        return (EXIT_FAILURE);
    environment = *env;
    target_length = ft_strlen(key);
    index = 0;
    while (environment->key[index]) 
    {
        current_length = ft_strlen(environment->key[index]);
        if (current_length == target_length && 
            !ft_strncmp(environment->key[index], key, target_length)) 
        {
            return (env_del_index(env, index));
        }
        index++;
    }
    return (EXIT_SUCCESS);
}

static char	no_value(t_env *env)
{
	char *empty_value;

	empty_value = ft_strdup("");
    if (!empty_value)
        return (EXIT_FAILURE);
    env->value = str_arr_realloc(env->value, empty_value);
    if (!env->value) 
	    return (free(empty_value), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char env_add(t_env *env, char *key, char *value)
{
    if (!env)
        return (EXIT_FAILURE);
    env->key = str_arr_realloc(env->key, key);
    if (!env->key)
        return (EXIT_FAILURE);
	else if(!value && no_value(env))
		return(EXIT_FAILURE);
	else
	{
		env->value = str_arr_realloc(env->value, value);
		if (!env->value)
			return (EXIT_FAILURE);
	} 
	env->len++;
    return (EXIT_SUCCESS);
}

char *env_find_value(t_env *env, char *key)
{
    size_t target_length;
    int index;

    if (!env || !key)
        return (NULL);
    target_length = ft_strlen(key);
    index = 0;
    while ( env->key[index])
    {
        if (ft_strlen(env->key[index]) == target_length && 
            !ft_strncmp(env->key[index], key, target_length)) 
        {
            return (env->value[index]);
        }
        index++;
    }    
    return (NULL);
}
