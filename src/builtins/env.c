/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:51 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/20 21:32:52 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void print_env_entry(const char *key, const char *value)
{
    write(STDOUT_FILENO, key, ft_strlen(key));
    write(STDOUT_FILENO, "=", 1);
    write(STDOUT_FILENO, value, ft_strlen(value));
    write(STDOUT_FILENO, "\n", 1);
}

void env(t_jobs *jobs)
{
    t_env *environment;
    int entry_index;
    
    environment = jobs->env;
    
    for (entry_index = 0; entry_index < environment->len; entry_index++) {
        print_env_entry(environment->key[entry_index],
                       environment->value[entry_index]);
    }
    
    jobs->mshell->quest_mark = 0;
}