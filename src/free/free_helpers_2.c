/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:53 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/22 11:03:09 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void free_cmd(t_mshell *mshell)
{
    if (mshell == NULL || mshell->jobs == NULL)
        return;

    t_job *current = mshell->jobs->job_list;
    while (current != NULL) {
        t_job *next_job = current->next_job;
        free_job(current);
        current = next_job;
    }

    mshell->jobs->job_list = NULL;
}

void free_array_ptr(char ***array)
{
    if (array == NULL || *array == NULL)
        return;

    free_array(*array);
    *array = NULL;
}

void free_env_struct(t_env *env)
{
    if (env == NULL)
        return;

    free_array_ptr(&env->key);
    free_array_ptr(&env->value);
    free(env);
}
