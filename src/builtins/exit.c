/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:57 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/24 16:19:30 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char *remove_quotes(char *input_str)
{
    char *clean_str;
    size_t str_len;
    int read_pos;
    int write_pos;

    str_len = ft_strlen(input_str);
    clean_str = malloc(str_len + 1);
    
    if (!clean_str)
        return (NULL);

    write_pos = 0;
    for (read_pos = 0; input_str[read_pos]; read_pos++) {
        if (input_str[read_pos] != '"' && input_str[read_pos] != '\'') {
            clean_str[write_pos++] = input_str[read_pos];
        }
    }
    clean_str[write_pos] = '\0';

    return (clean_str);
}

char exit_error(t_jobs *jobs, char *arg, const char *msg)
{
    const int EXIT_ERROR_CODE = 255;
    
    jobs->mshell->quest_mark = EXIT_ERROR_CODE;
    
    ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
    ft_putstr_fd(arg, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd((char *)msg, STDERR_FILENO);
    
    return (EXIT_FAILURE);
}

void exit_d(t_jobs *jobs, char **args)
{
    char *cleaned_arg;
    const char *MEMORY_ERROR = "memory allocation error\n";
    
    ft_putendl_fd("exit", STDOUT_FILENO);
    
    if (!args[1]) {
        jobs->mshell->quest_mark = 0;
        exit(jobs->mshell->quest_mark);
    }
    
    cleaned_arg = remove_quotes(args[1]);
    
    if (!cleaned_arg) {
        exit_error(jobs, args[1], MEMORY_ERROR);
        exit(jobs->mshell->quest_mark);
    }
    
    handle_exit_argument(jobs, args, cleaned_arg);
}