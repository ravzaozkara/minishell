/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:50 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/22 11:03:13 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void free_str_arr(char **array)
{
   int index;

   if (!array)
       return;

   for (index = 0; array[index]; index++) {
       free(array[index]);
   }
   free(array);
}

void free_jobs(t_jobs *jobs)
{
   t_job *current;
   t_job *next;

   if (!jobs)
       return;
       
   if (jobs->job_list) {
       current = jobs->job_list;
       while (current) {
           next = current->next_job;
           free_job_list(current);
           current = next;
       }
   }

   if (jobs->env)
       free_env(jobs->env);
       
   free(jobs);
}

void free_job_list(t_job *job)
{
   if (!job)
       return;
       
   if (job->args)
       free_str_arr_null(&job->args);
       
   if (job->redir) {
       free_redir(job->redir);
       job->redir = NULL;
   }
   
   free(job);
}

void free_redir(t_redir *redir)
{
   if (!redir)
       return;

   if (redir->files)
       free_str_arr_null(&redir->files);
   if (redir->eof)
       free_str_arr_null(&redir->eof);
   if (redir->in_f)
       free_str_arr_null(&redir->in_f);
   if (redir->out_f)
       free_str_arr_null(&redir->out_f);
   if (redir->app_f)
       free_str_arr_null(&redir->app_f);
       
   free(redir);
}

void free_mshell(t_mshell *mshell)
{
   if (!mshell)
       return;
       
   if (mshell->jobs)
       free_jobs(mshell->jobs);
       
   free(mshell);
}