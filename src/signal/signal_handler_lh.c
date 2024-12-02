/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_lh.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:57:00 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 20:01:27 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	main_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(130);
	}
}

void	set_signals(int context)
{
	if (context == MAIN)
	{
		signal(SIGINT, &main_signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (context == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (context == HDOC)
	{
		signal(SIGINT, &heredoc_signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
	}
}

void	initialize_file_descriptors(int fd_indexes[4])
{
	fd_indexes[0] = 0;
	fd_indexes[1] = 0;
	fd_indexes[2] = 0;
	fd_indexes[3] = -1;
}
