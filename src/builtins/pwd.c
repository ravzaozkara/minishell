/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:28:30 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 18:28:46 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	cmd_pwd(t_jobs *jobs)
{
	char		current_path[512];
	const int	error_status = 1;
	size_t		path_length;

	if (getcwd(current_path, sizeof(current_path)))
	{
		path_length = ft_strlen(current_path);
		write(STDOUT_FILENO, current_path, path_length);
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	else
	{
		jobs->mshell->quest_mark = error_status;
		perror("pwd");
		return (EXIT_FAILURE);
	}
}
