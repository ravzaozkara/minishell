/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:07:40 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 20:07:42 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_error(t_jobs *jobs, char *file, const char *message)
{
	jobs->mshell->quest_mark = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd((char *)message, STDERR_FILENO);
}

char	check_redir_error(t_jobs *jobs, t_job *job, char *file_path,
		int file_descriptor)
{
	t_stat	file_stat;

	if (file_descriptor == -1)
	{
		jobs->mshell->quest_mark = 1;
		if (stat(file_path, &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
				print_error(jobs, file_path, ": Is a directory\n");
			else
				print_error(jobs, file_path, ": No such file or directory\n");
		}
		else
		{
			print_error(jobs, file_path,
				": Failed to retrieve file information\n");
		}
		if (jobs->len == 1)
			return (EXIT_FAILURE);
		if (jobs->len > 1 || job->built_in == false)
			exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
