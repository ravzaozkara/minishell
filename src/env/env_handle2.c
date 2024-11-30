/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem <yunozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:20 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/21 20:27:54 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char get_first_env(t_jobs *jobs, char **env)
{
    char **env_parts;
    int env_index;

    jobs->env = ft_calloc(1, sizeof(t_env));
    if (!jobs->env)
        return (EXIT_FAILURE);

	env_index = 0;
    while (env[env_index]) 
	{
        env_parts = ft_split(env[env_index], '=');
        if (!env_parts)
            return (EXIT_FAILURE);
        else if (env_add(jobs->env, env_parts[0], env_parts[1]))
		{
            free_str_arr(env_parts);
            return (EXIT_FAILURE);
        }
        free_str_arr(env_parts);
		env_index++;
    }
    return (EXIT_SUCCESS);
}

static char copy_env_entries(t_env **env, t_env *new_env, int skip_index)
{
    bool skip_done;
    int write_index;

    skip_done = false;
    write_index = 0;
    while (write_index < new_env->len) 
	{
        int read_index = write_index + (write_index >= skip_index ? 1 : 0);
        
        new_env->key[write_index] = ft_strdup((*env)->key[read_index]);
        if (!new_env->key[write_index])
            return (free_env(new_env), EXIT_FAILURE);
            
        new_env->value[write_index] = ft_strdup((*env)->value[read_index]);
        if (!new_env->value[write_index])
            return (free_env(new_env), EXIT_FAILURE);
		write_index++;
    }
    
    return (EXIT_SUCCESS);
}

char env_del_index(t_env **env, int index)
{
    t_env *new_env;
    
    new_env = ft_calloc(1, sizeof(t_env));
    if (!new_env)
        return (EXIT_FAILURE);
    new_env->len = (*env)->len - 1;
	new_env->key = ft_calloc(new_env->len + 1, sizeof(char *));
    if (!new_env->key)
	{
		free(new_env);
        return (EXIT_FAILURE);
	}
    new_env->value = ft_calloc(new_env->len + 1, sizeof(char *));
    if (!new_env->value)
	{
        free(new_env->key);
		free(new_env);
        return (EXIT_FAILURE);
    }
    if (copy_env_entries(env, new_env, index))
        return (EXIT_FAILURE);
    free_env(*env);
    *env = new_env;
    
    return (EXIT_SUCCESS);
}
