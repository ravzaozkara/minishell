/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem < yunozdem@student.42istanbul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:26 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/22 01:10:27 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void run_cmd_error_ctrl(t_jobs *jobs, char *path)
{
    t_stat file_info;
    const int PERMISSION_ERROR = 126;
    const int NOT_FOUND_ERROR = 127;

    if (stat(path, &file_info) == -1)
        return;

    if (S_ISDIR(file_info.st_mode)) {
        jobs->mshell->quest_mark = 1;
        error_msg(jobs, path, ": Is a directory\n");
        exit(PERMISSION_ERROR);
    }

    if (!S_ISREG(file_info.st_mode)) {
        jobs->mshell->quest_mark = 1;
        error_msg(jobs, path, ": No such file or directory\n");
        exit(NOT_FOUND_ERROR);
    }

    if (access(path, R_OK) != 0) {
        jobs->mshell->quest_mark = 1;
        error_msg(jobs, path, ": Permission denied\n");
        exit(PERMISSION_ERROR);
    }
}

static char *accessor(char *env_path, char *cmd)
{
    char **path_directories;
    char *full_path;
    char *dir_with_slash;
    int i;

    if (!(path_directories = ft_split(env_path, ':')))
        return (NULL);

    for (i = 0; path_directories[i]; i++) {
        if (!(dir_with_slash = ft_strjoin_const(path_directories[i], "/")))
            continue;
        
        full_path = ft_strjoin(dir_with_slash, cmd);
        free(dir_with_slash);
        
        if (!full_path) {
            free_str_arr(path_directories);
            return (NULL);
        }
        
        if (access(full_path, X_OK) == 0) {
            free_str_arr(path_directories);
            return (full_path);
        }
        free(full_path);
    }
    free_str_arr(path_directories);
    return (NULL);
}

static char *get_exec_path(t_jobs *jobs, t_job *job, char *env_path)
{
    char *executable_path;

    if (ft_strchr(job->args[0], '/')) {
        run_cmd_error_ctrl(jobs, job->args[0]);
        executable_path = ft_strdup(job->args[0]);
    } else {
        executable_path = accessor(env_path, job->args[0]);
    }

    if (!executable_path) {
        error_msg(jobs, job->args[0], ": command not found\n");
        exit(127);
    }

    return executable_path;
}

static char handle_env_path_null(t_jobs *jobs, t_job *job, char **env)
{
    const int NO_PATH_ERROR = 127;

    if (access(job->args[0], X_OK) == 0) {
        execve(job->args[0], job->args, env);
        exit(NO_PATH_ERROR);
    }

    jobs->mshell->quest_mark = 1;
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(job->args[0], STDERR_FILENO);
    ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
    return (EXIT_FAILURE);
}

void run_cmd(t_jobs *jobs, t_job *job)
{
    char **environment;
    char *executable_path;
    char *path_var;
    const int EXEC_FAILURE = 127;

    path_var = env_find_value_const(jobs->env, "PATH");
    environment = get_env_for_exec(jobs->env);

    if (!path_var) {
        if (handle_env_path_null(jobs, job, environment))
            return;
    }

    executable_path = get_exec_path(jobs, job, path_var);
    jobs->mshell->quest_mark = 0;
    
    execve(executable_path, job->args, environment);
    exit(EXEC_FAILURE);
}