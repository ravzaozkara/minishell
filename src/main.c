/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:27:44 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 21:30:05 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	reset_jobs(t_mshell *mshell)
{
	t_job	*current;
	t_job	*next;

	current = mshell->jobs->job_list;
	while (current)
	{
		next = current->next_job;
		free_job(current);
		current = next;
	}
	mshell->jobs->job_list = ft_calloc(1, sizeof(t_job));
	if (!mshell->jobs->job_list)
		return (EXIT_FAILURE);
	mshell->jobs->job_list->redir = ft_calloc(1, sizeof(t_redir));
	if (!mshell->jobs->job_list->redir)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_mshell	*initialize_mshell(char **env)
{
	t_mshell	*mshell;

	mshell = ft_calloc(1, sizeof(t_mshell));
	if (!mshell)
		return (NULL);
	mshell->jobs = ft_calloc(1, sizeof(t_jobs));
	if (!mshell->jobs)
		return (free(mshell), NULL);
	if (env_init(mshell->jobs, env))
		return (free(mshell->jobs), free(mshell), NULL);
	mshell->jobs->mshell = mshell;
	return (mshell);
}

static char	execute_process(t_mshell *mshell, char *prompt)
{
	if (parse_cmd(mshell->jobs, prompt))
		return (EXIT_FAILURE);
	if (exec_cmd(mshell))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	run_mshell(t_mshell *mshell)
{
	char	*prompt;
	char	*trimmed_prompt;

	while (1)
	{
		set_signals(MAIN);
		prompt = readline(PROMPT);
		if (!prompt)
			break ;
		trimmed_prompt = ft_strtrim(prompt, " \t\r\f\v");
		free(prompt);
		if (!trimmed_prompt)
			break ;
		set_signals(SIGNAL_IGNORE);
		if (reset_jobs(mshell))
		{
			free(trimmed_prompt);
			break ;
		}
		if (execute_process(mshell, trimmed_prompt))
			continue ;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mshell	*mshell;

	(void)argv;
	if (argc != 1)
		return (1);
	mshell = initialize_mshell(env);
	if (!mshell)
		return (EXIT_FAILURE);
	run_mshell(mshell);
	free_shell(mshell);
	return (EXIT_SUCCESS);
}
