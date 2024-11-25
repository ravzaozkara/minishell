/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:49 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/24 22:42:04 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int is_n_flag(char *arg)
{
	int i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void echo(t_jobs *jobs, t_job *job)
{
	int i;
	int newline;

	newline = 1;
	i = 1;
	while (job->args[i] && is_n_flag(job->args[i]))
	{
		newline = 0;
		i++;
	}

	while (job->args[i])
	{
		if (job->args[i][0] == '\0')
			ft_putchar_fd('\0', 1);
		else
			ft_putstr_fd(job->args[i], 1);
		if (job->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	jobs->mshell->quest_mark = 0;
}
