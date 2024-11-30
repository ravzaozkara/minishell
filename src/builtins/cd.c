/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:36 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/20 21:32:37 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char cd(t_jobs *jobs, char *path)
{
    char *target_directory;
    const int DIRECTORY_ERROR = 1;

    target_directory = path;
    
    if (!target_directory) {
        target_directory = env_find_value_const(jobs->env, "HOME");
        
        if (!target_directory) {
            jobs->mshell->quest_mark = DIRECTORY_ERROR;
            return (EXIT_FAILURE);
        }
    }
    
    if (chdir(target_directory) == -1) {
        jobs->mshell->quest_mark = DIRECTORY_ERROR;
        perror("cd");
        return (EXIT_FAILURE);
    }
    
    jobs->mshell->quest_mark = 0;
    return (EXIT_SUCCESS);
}