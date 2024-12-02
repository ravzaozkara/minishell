/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem < yunozdem@student.42istanbul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:43 by nozkara            #+#    #+#             */
/*   Updated: 2024/11/22 00:51:59 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "dirent.h"
#include "errno.h"
#include "fcntl.h"
#include "libft/libft.h"
#include "signal.h"
#include "stdbool.h"
#include "stdio.h"
#include "sys/stat.h"
#include "sys/wait.h"
#include "unistd.h"
#include <readline/history.h>
#include <readline/readline.h>

#define PROMPT "mini <'v'> "

#define QUOTES "'\""
#define DQUOTE '\"'
#define SQUOTE '\''

#define MAIN 0
#define CHILD 1
#define HDOC 2
#define SIGNAL_IGNORE 1618

typedef struct s_redir t_redir;
typedef struct s_job t_job;
typedef struct s_jobs t_jobs;
typedef struct s_mshell t_mshell;
typedef struct s_env t_env;
typedef struct s_quote_state t_quote_state;
typedef struct s_parser_state t_parser_state;
typedef struct stat t_stat;

struct s_redir
{
    char last_out;
    char last_in;
    int out_file;
    int app_file;
    int in_file;
    char **out_f;
    char **app_f;
    char **in_f;
    char **eof;
    char **files;
};

struct s_job
{
    pid_t pid;
    char built_in;
    char **args;
    int args_len;
    t_redir *redir;
    t_job *next_job;
};

struct s_jobs
{
    t_mshell *mshell;
    t_env *env;
    t_job *job_list;
    int len;
};

struct s_mshell
{
    t_jobs *jobs;
    int quest_mark;
    int backup[2];
};

struct s_env
{
    char **key;
    char **value;
    int len;
};

struct s_quote_state
{
    bool in_single;
    bool in_double;
};

struct s_parser_state
{
    t_quote_state *quote_state;
    int index;
    int length;
};

void free_array(char **arr);
void free_all_jobs(t_jobs *jobs);
void free_redirs(t_redir *redir);
void free_job(t_job *job);
void free_shell(t_mshell *mshell);
void free_env_struct(t_env *env);
void free_array_ptr(char ***arr);
void free_cmd(t_mshell *mshell);

char exec_cmd(t_mshell *mshell);
char pipe_no(t_jobs *jobs, t_job *job);
char handle_pipe(t_jobs *jobs, t_job *job);
void restore_io(t_mshell *mshell);
void exec_process(t_jobs *jobs, t_job *job);
char **array_to_env(t_env *env);

char env_add(t_env *env, char *key, char *value);
char env_remove(t_env **env, char *key, char *value);
char *env_find_value(t_env *env, char *key);
char env_delete(t_env **env, int index);
char env_init(t_jobs *jobs, char **env);


int handle_redir(t_jobs *jobs, t_job *job, int indexes[5]);
char handle_heredoc(t_jobs *jobs, t_job *job, char state);
int get_redirs(t_jobs *jobs, t_job *job);
char check_redir_error(t_jobs *jobs, t_job *job, char *file_i, int fd);

void toggle_quotes(t_quote_state *state, char c);

void cmd_echo(t_jobs *jobs, t_job *job);
char cmd_cd(t_jobs *jobs, char *path);
char cmd_pwd(t_jobs *jobs);
void cmd_env(t_jobs *jobs);
char export(t_jobs *jobs, char **args);
char cmd_unset(t_env **env, char **keys);
void check_builtin(t_job *job);
char exec_builtin(t_jobs *jobs, t_job *job);
char env_update(t_env *env, char *key, char *value);
void cmd_exit(t_jobs *jobs, char **args);
void handle_exit_args(t_jobs *jobs, char **args, char *stripped);


char handle_token(t_job *job, char *arg, char *redir_status);
char parse_cmd(t_jobs *jobs, char *prompt);
char **tokenize(char *input);


void expand_cmd(t_jobs *jobs, char **prompt);
char check_redir(t_redir *redir, char *arg);
char *expand_vars(t_jobs *jobs, char *prompt);
int calc_expanded_len(t_jobs *jobs, char *prompt, t_quote_state state);
char **array_to_env(t_env *env);


bool is_special_char(const char *token);
bool has_unclosed_quotes(t_jobs *jobs, const char *input);
bool has_syntax_errors(t_jobs *jobs, char **tokens);


void set_signals(int c);
void handle_sigint(int sig);


char *str_join(char *s1, const char *s2);
int arr_len(char **arr);
char **arr_append(char **arr, char *element);
void print_error(t_jobs *jobs, char *file, const char *message);
char *env_getval(t_env *env, const char *key);
char print_exit_error(t_jobs *jobs, char *arg, const char *msg);

#endif
