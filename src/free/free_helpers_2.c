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

void free_nec(t_mshell *mshell)
{
   t_job *current;
   t_job *next;

   if (!mshell || !mshell->jobs)
       return;

   current = mshell->jobs->job_list;
   while (current) {
       next = current->next_job;
       free_job_list(current);
       current = next;
   }
   
   mshell->jobs->job_list = NULL;
}

void free_str_arr_null(char ***array)
{
   if (!array || !*array)
       return;
       
   free_str_arr(*array);
   *array = NULL;
}

void free_env(t_env *env)
{
   if (!env)
       return;
       
   free_str_arr_null(&env->key);
   free_str_arr_null(&env->value);
   free(env);
}