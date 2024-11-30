/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:07 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/20 21:33:08 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char unset(t_env **env, char **keys)
{
    char *env_value;
    int key_index;

    if (!*env)
        return (EXIT_FAILURE);
        
    if (!keys)
        return (EXIT_SUCCESS);

    for (key_index = 0; keys[key_index]; key_index++) {
        env_value = env_find_value(*env, keys[key_index]);
        
        if (!env_value)
            continue;
            
        if (env_del_element(env, keys[key_index], env_value))
            return (EXIT_FAILURE);
    }
    
    return (EXIT_SUCCESS);
}