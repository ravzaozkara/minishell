/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle_lh1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:05:11 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 20:06:19 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	compare_strings(char *input, char *delimiter)
{
	int	input_length;
	int	delimiter_length;

	input_length = ft_strlen(input);
	delimiter_length = ft_strlen(delimiter);
	return (!ft_strncmp(input, delimiter, input_length)
		&& input_length == delimiter_length);
}

void	handle_arguments(t_jobs *jobs, t_job *job, int pipe_fds[2])
{
	char	*argument;
	char	current_status;
	int		index;

	index = 0;
	while (job->redir->eof[index])
	{
		argument = readline("> ");
		if (!argument)
		{
			jobs->mshell->quest_mark = 130;
			exit(jobs->mshell->quest_mark);
		}
		current_status = compare_strings(argument, job->redir->eof[index]);
		if (!current_status && argument && !job->redir->eof[index + 1])
			ft_putendl_fd(argument, pipe_fds[1]);
		if (current_status)
			index++;
		free(argument);
	}
}
