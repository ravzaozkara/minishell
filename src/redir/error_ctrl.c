/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:18 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/20 21:34:19 by nozkara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void error_msg(t_jobs *jobs, char *file, const char *message)
{
    // quest_mark değerini 1 olarak ayarla (hata durumunu gösterir)
    jobs->mshell->quest_mark = 1;

    // Hata mesajını standart hata çıktısına yazdır
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(file, STDERR_FILENO);
    ft_putstr_fd((char *)message, STDERR_FILENO);
}

char redir_error(t_jobs *jobs, t_job *job, char *file_path, int file_descriptor)
{
    t_stat file_stat;

    if (file_descriptor == -1)
    {
        jobs->mshell->quest_mark = 1;

        if (stat(file_path, &file_stat) == 0)
        {
            if (S_ISDIR(file_stat.st_mode))
                error_msg(jobs, file_path, ": Is a directory\n");
            else
                error_msg(jobs, file_path, ": No such file or directory\n");
        }
        else
        {
            error_msg(jobs, file_path, ": Failed to retrieve file information\n");
        }

        if (jobs->len == 1)
            return EXIT_FAILURE;

        if (jobs->len > 1 || job->built_in == false)
            exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
