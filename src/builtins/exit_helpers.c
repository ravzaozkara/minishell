/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:21:30 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 18:22:37 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "limits.h"

static bool	check_numeric_overflow(long current_value, char next_digit)
{
	long	digit_value;

	digit_value = next_digit - '0';
	return (current_value > (LONG_MAX - digit_value) / 10);
}

static char	process_numeric_string(const char *str, int *pos, long *result)
{
	while (str[*pos] && ft_isdigit(str[*pos]))
	{
		if (check_numeric_overflow(*result, str[*pos]))
			return (EXIT_FAILURE);
		*result = (*result * 10) + (str[*pos] - '0');
		(*pos)++;
	}
	return (EXIT_SUCCESS);
}

static int	calculate_exit_status(char *str)
{
	long	numeric_value;
	int		sign_multiplier;
	int		index;

	index = 0;
	while (str[index] && ((str[index] >= 9 && str[index] <= 13)
			|| str[index] == ' '))
		index++;
	sign_multiplier = 1;
	if (str[index] == '-')
	{
		sign_multiplier = -1;
		index++;
	}
	else if (str[index] == '+')
	{
		index++;
	}
	numeric_value = 0;
	if (process_numeric_string(str, &index, &numeric_value))
		return (EXIT_FAILURE);
	numeric_value = (numeric_value * sign_multiplier) % 256;
	return ((numeric_value < 0) ? numeric_value + 256 : numeric_value);
}

static bool	validate_numeric_string(char *str)
{
	int	index;

	if (!str || !*str)
		return (false);
	index = 0;
	if (str[index] == '-' || str[index] == '+')
		index++;
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (false);
		index++;
	}
	return (true);
}

void	handle_exit_args(t_jobs *jobs, char **args, char *stripped)
{
	const char	*too_many_args_msg = "minishell: exit: too many arguments\n";

	if (!validate_numeric_string(stripped))
	{
		print_exit_error(jobs, args[1], "numeric argument required\n");
		free(stripped);
		exit(jobs->mshell->quest_mark);
	}
	if (args[2])
	{
		jobs->mshell->quest_mark = 1;
		write(STDERR_FILENO, too_many_args_msg, 37);
		free(stripped);
		return ;
	}
	jobs->mshell->quest_mark = calculate_exit_status(stripped);
	free(stripped);
	exit(jobs->mshell->quest_mark);
}
