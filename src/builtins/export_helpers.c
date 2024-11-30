/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:59 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/24 17:09:32 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char update_env(t_env *env, char *key, char *value)
{
    const int ENV_UPDATE_ERROR = -1;
    size_t target_key_length;
    int env_index;
    char *new_value;

    if (!env || !key || !value)
        return (ENV_UPDATE_ERROR);

    target_key_length = ft_strlen(key);
    
    for (env_index = 0; env->key[env_index]; env_index++) {
        if (ft_strlen(env->key[env_index]) == target_key_length && 
            !ft_strncmp(env->key[env_index], key, target_key_length)) {
            
            new_value = ft_strdup(value);
            if (!new_value)
                return (ENV_UPDATE_ERROR);
                
            free(env->value[env_index]);
            env->value[env_index] = new_value;
            
            return (EXIT_SUCCESS);
        }
    }
    
    return (EXIT_FAILURE);
}