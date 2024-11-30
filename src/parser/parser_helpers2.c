/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:05 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/20 21:44:41 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char check_redirection(char **redirection_list, char *cleaned_arg)
{
   int list_length;
   size_t arg_length;
   size_t last_redir_length;

   if (!redirection_list)
       return (EXIT_SUCCESS);
       
   list_length = str_arr_len(redirection_list);
   arg_length = ft_strlen(cleaned_arg);
   last_redir_length = ft_strlen(redirection_list[list_length - 1]);

   if (last_redir_length == arg_length && 
       !ft_strncmp(redirection_list[list_length - 1], 
                   cleaned_arg, last_redir_length)) {
       return (EXIT_FAILURE);
   }
   
   return (EXIT_SUCCESS);
}

char ctrl_append(t_redir *redir, char *arg)
{
   char *trimmed_arg;
   const int APPEND_ERROR = 1;

   trimmed_arg = ft_strtrim(arg, "\"");
   if (!trimmed_arg)
       return (APPEND_ERROR);

   if (check_redirection(redir->app_f, trimmed_arg) || 
       check_redirection(redir->in_f, trimmed_arg) ||
       check_redirection(redir->out_f, trimmed_arg) || 
       check_redirection(redir->eof, trimmed_arg)) {
       free(trimmed_arg);
       return (APPEND_ERROR);
   }

   free(trimmed_arg);
   return (0);
}