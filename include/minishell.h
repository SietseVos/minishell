/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:39:06 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 17:57:07 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

// # define uint32_t u_int32_t linux stuff
// # define uint64_t u_int64_t

# define OLD 		3
# define NULL_TERM	1

# define PIPE_READ	0
# define PIPE_WRITE	1

# define TOKEN_ERROR "minishell: syntax error near unexpected token `"
# define NL_ERROR "minishell: syntax error near unexpected token `newline'\n"
# define PIPE_ERROR "minishell: pipe: Resource temporarily unavailable\n"
# define FORK_ERROR "minishell: fork: Resource temporarily unavailable\n"
# define UNSET_ERROR "bash: unset: `"
# define EXPORT_ERROR "bash: export: `"
# define IDENT_ERROR "': not a valid identifier\n"
# define AMBIGU_ERROR ": ambiguous redirect\n"

/**
 * open file read mode
 * open file append mode
 * run heredoc
 * open file trunc mode
 * empty node with pipe
 * command
 * heredoc without quote
 * heredoc with quote
 * beware of this dangerous monster D:
*/
enum e_type
{
	INFILE,
	APPEND,
	HDOC,
	TRUNC,
	PIPE,
	TOSTDOUT,
	HDOCSPACE,
	HDOCQUOTE,
	AMBIGU
};

struct s_global_info
{
	int32_t	exit_status;
	pid_t	heredoc_pid;
	bool	heredoc_breakout;
}	global_t_info;

struct s_global_info	g_info;

typedef struct s_action
{
	char			**arg;
	int32_t			type;
	struct s_action	*next;
}	t_action;

typedef struct s_child_pids
{
	pid_t				pid;
	struct s_child_pids	*next;
}	t_child_pids;

typedef struct s_env_vars
{
	char				*str;
	bool				has_value;
	struct s_env_vars	*next;
}	t_env_vars;

typedef struct s_heredoc
{
	char				*path;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_info
{
	t_action	**action;
	t_env_vars	**list;
}	t_info;

/* ---------------------------	builtins	------------------------------ */

int32_t			cd(char **argument, t_env_vars **env);
int32_t			create_new_oldpwd_node(t_env_vars **env);
int32_t			chdir_error(char *str);
char			*create_new_cd_str(char *var, char *pwd);
int32_t			set_oldpwd(t_env_vars *oldpwd_node);
int32_t			move_pwd_to_oldpwd(t_env_vars *oldpwd_node, \
									t_env_vars *pwd_node, bool *has_been_null);
int32_t			create_empty_oldpwd(t_env_vars *oldpwd_node, \
											bool *has_been_null);
void			exit_shell(char **argument, bool print);
void			pwd(void);
void			env(t_env_vars *list);
int32_t			strings_in_array(char **str);
int32_t			export(char **args, t_env_vars **env);
void			bubble_sort_array(char **env_strings, int32_t lst_size);
int32_t			add_quotes_after_equal(char **strings);
bool			is_already_in_list(char	*input, t_env_vars *env);
void			unset(char **arg, t_env_vars **list);
void			echo(char **args);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* --------------------------	env_functions	-------------------------- */

int32_t			add_env_node(t_env_vars **env, char *str);
bool			create_env_vars_list(char **envp, t_env_vars **env_head);
bool			clean_env_vars_list(t_env_vars **env_head);
char			**free_array_till_index(char **array, int32_t index);
char			**env_list_to_array(t_env_vars *env_list);
int32_t			env_list_size(t_env_vars *env_list);
t_env_vars		*get_variable_node(t_env_vars *list, char *variable);
void			set_env_list_bool_value(t_env_vars *env);
void			set_env_node_hasvalue(t_env_vars *env);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ---------------------------	executer	------------------------------ */

int32_t			executer(t_action **actions, t_env_vars **list);
void			reset_pid(void);
int32_t			save_pid(pid_t new_pid);
t_child_pids	*get_last_pid_node(void);
t_child_pids	*get_first_pid_node(void);
void			set_exit_status_and_wait(void);
char			*get_executable_path(char **arguments, t_env_vars *list);
int32_t			execute_command(char **arguments, t_env_vars *list);
bool			actions_only_builtins(t_action *actions);
bool			contains_pipes(t_action *actions);
void			set_actions_next_pipe(t_action **actions);
void			pop_nodes_till_command(t_action **actions);
void			run_child(t_info info, int32_t *fd, \
							int32_t fd_in, bool contains_pipes);
bool			run_if_builtin_child(t_info info);
int32_t			run_builtin_no_pipe(t_action **actions, t_env_vars **list);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* _----------------------------	redirects	-------------------------- */

int32_t			get_infile_fd(t_action	*action);
int32_t			get_outfile_fd(t_action	*action);
int32_t			set_redirections(t_action *actions, int32_t *in_fd, \
												int32_t *out_fd);
void			reset_redirections(int32_t in_fd, int32_t out_fd);
int32_t			create_heredoc_file(t_action *heredoc_node, \
												t_heredoc **file_paths);
int32_t			heredoc(t_action *actions, t_heredoc **file_paths, \
												t_env_vars *env);
void			remove_heredoc_files(t_heredoc **files);
int32_t			expand_heredoc(char **input, int32_t type, t_env_vars *env);
int32_t			close_free_and_return(int32_t fd, char *str1, \
												char *str2, int32_t return_v);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ------------------------------	lexer	------------------------------ */

char			*lexer(char *input);
bool			in_string(char c, bool reset);
void			skip_string(char *str, int32_t *i);
bool			check_syntax_error(char *str);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ------------------------------	parser	------------------------------ */

int32_t			envvarlen(char *str, char end);
int32_t			is_operator(char c);
int32_t			check_str_end(char *str, int32_t i, int32_t n);
void			place_str_in_node(char *dst, char *src, \
											int32_t *i, t_env_vars *envp);
void			place_hdoc_in_node(char *dst, char *src, int32_t *i);
int32_t			place_envvar(char *dst, char *src, \
											t_env_vars *envp, int32_t *i);
t_action		*parse_file(char *input, int32_t *i, t_env_vars *envp);
t_action		*parse_cmd(char *input, int32_t *i, t_env_vars *envp);
int32_t			skipstring(char *str, char quote);
void			read_input_str(char *str, int *strlen, t_env_vars *envp);
void			read_hdoc_str(char *str, int *strlen);
t_action		*parser(char *input, t_env_vars *envp);
t_action		*parse_pipe(char *input, int32_t *i);
bool			join_split_cmds(t_action *lst);
bool			merge_nodes(t_action *dst, t_action **src, \
												t_action **prevnextptr);
bool			is_whitespace(char c);
int32_t			interpvar_strlen(char *str, char c, \
									int32_t *strlen, t_env_vars *envp);
int32_t			place_envvar_space(char *dst, char *src, \
											t_env_vars *envp, int32_t *j);

void			print_actions(t_action *inlst);
t_action		*found_ambigu(char *input, int32_t *i);
bool			ambigu_redirect(char *input, int32_t i, t_env_vars *envp);
void			skip_operator_space(char *input, int32_t *i);
void			print_actions(t_action *inlst);
int32_t			place_envvar_space(char *dst, char *src, \
											t_env_vars *envp, int32_t *j);
int32_t			place_envvar_quote(char *dst, char *src, \
											t_env_vars *envp, int32_t *j);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ------------------------------	signals	------------------------------ */

void			init_signals(void);
void			handle_sig_executer(int32_t sig);
void			sig_c_outside_fork(int32_t sig);
void			heredoc_handler(int32_t sig);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ------------------------------	utils	------------------------------ */

int32_t			cd_home_path_not_set(void);
bool			boolerr(char *errmsg);
void			*nullerr(char *errmsg);
void			print_actions(t_action *inlst);
void			printenvp(t_env_vars *print);
void			printchararr(char **toprint);
void			free_double_array(char **array);
void			pop_action_node(t_action **node);
void			free_action_list(t_action **node);
void			free_env_list(t_env_vars *list);
bool			free_env_list_return_false(t_env_vars *env);
void			write_error_with_chars(char *str1, char char1, \
													char char2, char *str2);
void			write_error_with_strings(char *str1, char *str2, char *str3);
int32_t			return_with_error_message(char *str1, const char *str2, \
											char *str3, int32_t return_value);
int32_t			close_fd_return_error(char *error_message, int32_t fd, \
				int32_t return_value);
void			exit_with_error_message(char *str1, char *str2, char *str3, \
				int32_t exit_value);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

#endif
