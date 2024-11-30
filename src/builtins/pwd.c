/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:05 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/20 21:33:06 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char pwd(t_jobs *jobs)
{
    char current_path[512];
    const int ERROR_STATUS = 1;
    size_t path_length;

    if (!getcwd(current_path, sizeof(current_path))) {
        jobs->mshell->quest_mark = ERROR_STATUS;
        perror("pwd");
        return (EXIT_FAILURE);
    }

    path_length = ft_strlen(current_path);
    write(STDOUT_FILENO, current_path, path_length);
    write(STDOUT_FILENO, "\n", 1);
    
    return (EXIT_SUCCESS);
}