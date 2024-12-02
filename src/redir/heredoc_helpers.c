/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:52:38 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 19:53:36 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	initialize_fd_indexes(int indexes[4])
{
	indexes[0] = 0;
	indexes[1] = 0;
	indexes[2] = 0;
	indexes[4] = -1;
}

int	handle_redirection_setup(t_jobs *jobs, int fd)
{
	if (fd == -1)
	{
		jobs->mshell->quest_mark = 1;
		return (-1);
	}
	return (0);
}
