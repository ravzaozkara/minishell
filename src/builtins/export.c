/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozkara <nozkara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:26:46 by nozkara           #+#    #+#             */
/*   Updated: 2024/12/02 21:24:27 by nozkara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	report_export_error(t_jobs *jobs, char *arg, const char *msg)
{
	jobs->mshell->quest_mark = 1;
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putendl_fd((char *)msg, STDERR_FILENO);
	return (EXIT_FAILURE);
}

static char	validate_identifier(char *arg, bool check_equals)
{
	bool	has_alpha;
	int		index;

	has_alpha = false;
	index = 0;
	while (arg[index])
	{
		if (check_equals && arg[index] == '=')
			index++;
		if (ft_isalpha(arg[index]))
			has_alpha = true;
		if (!ft_isalnum(arg[index]) && arg[index] != '_')
			return (EXIT_FAILURE);
		index++;
	}
	if (has_alpha)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static char	process_export_arg(t_jobs *jobs, char *arg)
{
	char	*key;
	char	*value;
	int		equals_pos;
	char	update_status;

	equals_pos = 0;
	while (arg[equals_pos] && arg[equals_pos] != '=')
		equals_pos++;
	key = ft_substr(arg, 0, equals_pos);
	if (!key)
		return (EXIT_FAILURE);
	if (validate_identifier(key, false))
		return (free(key), \
			report_export_error(jobs, arg, "not a valid identifier"));
	value = ft_substr(arg, equals_pos + 1, ft_strlen(arg) - equals_pos);
	if (!value)
		return (free(key), EXIT_FAILURE);
	update_status = env_update(jobs->env, key, value);
	if (update_status == -1)
		return (free(key), free(value), EXIT_FAILURE);
	if (update_status && env_add(jobs->env, key, value))
		return (free(key), free(value), EXIT_FAILURE);
	return (free(key), free(value), EXIT_SUCCESS);
}

static void	display_exported_values(t_env *env)
{
	int	index;

	index = 0;
	while (index < env->len)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->key[index], STDOUT_FILENO);
		if (env->value[index][0])
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env->value[index], STDOUT_FILENO);
			ft_putstr_fd("\"\n", STDOUT_FILENO);
		}
		else
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		index++;
	}
}

char	export(t_jobs *jobs, char **args)
{
	int	arg_index;

	if (!args[1])
	{
		display_exported_values(jobs->env);
		jobs->mshell->quest_mark = 0;
		return (EXIT_SUCCESS);
	}
	arg_index = 1;
	while (args[arg_index])
	{
		if (process_export_arg(jobs, args[arg_index]))
			return (EXIT_FAILURE);
		arg_index++;
	}
	return (EXIT_SUCCESS);
}
