#ifndef  MINISHELL_H
# define MINISHELL_H
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

#define uint32_t u_int32_t
#define uint64_t u_int64_t

#define null	1
#define old 	3
#define quotes	2

#define	PIPE_READ	0
#define PIPE_WRITE	1

// legacy code
#define ruben int8_t 	// this was orginally used as a solution to a complitaced problem ruben (cat), ruben (the best) and int32_t encouncered during their adventures in minihell
#define sietse int32_t	// sietse also wanted to feel special so we made him a data type aswell :)

enum type
{
	INFILE,				// open file read mode
	APPEND,				// open file append mode
	HDOC,				// run heredoc
	TRUNC,				// open file trunc mode
	PIPE,				// empty node with pipe
	TOSTDOUT,			// command
};

int32_t	g_exit_status;

typedef struct action_s
{
	char			**arg;
	int32_t			type;
	struct action_s *next;
}	action_t;

typedef struct child_pids_s
{
	pid_t				pid;
	struct child_pids_s	*next;
}	child_pids_t;

typedef struct env_vars_s
{
	char				*str;
	bool				has_value;
	struct env_vars_s	*next;
}	env_vars_t;

typedef struct heredoc_s
{
	char				*path;
	struct heredoc_s	*next;
}	heredoc_t;


typedef	struct info_s
{
	action_t	**action;
	env_vars_t	**list;
}	info_t;

/* ---------------------------	builtins	------------------------------ */

	int32_t		cd(char **argument, env_vars_t **env);
	int32_t		chdir_error(char *str);
	char		*create_new_cd_str(char *var, char *pwd);
	int32_t		set_oldpwd(env_vars_t *oldpwd_node);
	int32_t		move_pwd_to_oldpwd(env_vars_t *oldpwd_node, env_vars_t *pwd_node, bool *has_been_null);
	int32_t		create_empty_oldpwd(env_vars_t *oldpwd_node, bool *has_been_null);
	void		exit_shell(char **argument, bool print);
	void		pwd(void);
	void		env(env_vars_t *list);
	int32_t		strings_in_array(char **str);
	int32_t		export(char **args, env_vars_t **env);
	void		bubble_sort_array(char **env_strings, int32_t lst_size);
	int32_t		add_quotes_after_equal(char **strings);
	bool		is_already_in_list(char	*input, env_vars_t *env);
	void		unset(char **arg, env_vars_t **list);
	void		echo(char **args);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* --------------------------	env_functions	-------------------------- */

int32_t			add_env_node(env_vars_t **env, char *str);
bool			create_env_vars_list(char **envp, env_vars_t **env_head);
char			**free_array_till_index(char **array, int32_t index);
char			**env_list_to_array(env_vars_t *env_list);
int32_t			env_list_size(env_vars_t *env_list);
env_vars_t		*get_variable_node(env_vars_t *list, char *variable);
void			set_env_list_bool_value(env_vars_t *env);
void			set_env_node_hasvalue(env_vars_t *env);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ---------------------------	executer	------------------------------ */

int32_t			executer(action_t **actions, env_vars_t **list);
void			reset_pid(void);
int32_t			save_pid(pid_t new_pid);
child_pids_t	*get_last_pid_node(void);
child_pids_t	*get_first_pid_node(void);
void			set_exit_status_and_wait(void);
char			*get_executable_path(char **arguments, env_vars_t *list);
int32_t			execute_command(char **arguments, env_vars_t *list);
bool			actions_only_builtins(action_t *actions);
bool			contains_pipes(action_t *actions);
void			set_actions_next_pipe(action_t **actions);
void			pop_nodes_till_command(action_t **actions);
void			run_child(info_t info, int32_t *fd, int32_t fd_in, bool contains_pipes);
bool			run_if_builtin_child(info_t info);
int32_t			run_builtin_no_pipe(action_t **actions, env_vars_t **list);

//				old executer
int32_t			pipe_command(action_t *acts, int32_t fdread, char **envp);
char			*get_executable(char *cmd, char **envp);
int				pplen(char **pp);
void			free_pp(char **pp, int size);
void			pipe_to_file(char **cmd, int32_t fdread, int32_t fdwrite, char **envp);
bool			executer_setup(action_t *acts, env_vars_t *envp);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* _----------------------------	redirects	-------------------------- */

int32_t			get_infile_fd(action_t	*action);
int32_t			get_outfile_fd(action_t	*action);
int32_t			set_redirections(action_t *actions, int32_t *in_fd, int32_t *out_fd);
void			reset_redirections(int32_t in_fd, int32_t out_fd);
int32_t			create_heredoc_file(action_t *heredoc_node, heredoc_t **file_paths);
int32_t			heredoc(action_t *actions, heredoc_t **file_paths);
void			remove_heredoc_files(heredoc_t **files);

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

int32_t			strlen_til_space(char *str, env_vars_t *envp);
int32_t			strlen_til_quote(char *str, char c, env_vars_t *envp);
int32_t			envvarlen(char *str, char end);
int32_t			is_operator(char c);
int32_t			check_str_end(char *str, int32_t i, int32_t n);
void			place_str_in_node(char *dst, char *src, int32_t *i, env_vars_t *envp);
int32_t			place_envvar(char *dst, char *src, env_vars_t *envp, int32_t *i);
action_t		*parse_file(char *input, int32_t *i, env_vars_t *envp);
action_t		*parse_cmd(char *input, int32_t *i, env_vars_t *envp);
int32_t			skipstring(char *str, char quote);
void			read_input_str(char *str, int *strlen, env_vars_t *envp);
action_t		*parser(char *input, env_vars_t *envp);
action_t		*parse_pipe(char *input, int32_t *i);
bool			join_split_cmds(action_t *lst);
bool			merge_nodes(action_t *dst, action_t *src, action_t **prevnextptr);
bool			is_whitespace(char c);

void	print_actions(action_t *inlst);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ------------------------------	signals	------------------------------ */

void			init_signals(void);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ------------------------------	utils	------------------------------ */

bool			boolerr(char *errmsg);
void			*nullerr(char *errmsg);
void			print_actions(action_t *inlst);
void			printenvp(env_vars_t *print);
void			printchararr(char **toprint);
void			free_double_array(char **array);
void			pop_action_node(action_t **node);
void			free_action_list(action_t **node);
void			free_env_list(env_vars_t *list);
void			write_error_with_chars(char *str1, char char1, char char2, char *str2);
void			write_error_with_strings(char *str1, char *str2, char *str3);
int32_t			return_with_error_message(char *str1, const char *str2, char *str3, \
				int32_t return_value);
int32_t			close_fd_return_error(char *error_message, int32_t fd, \
				int32_t return_value);
void			exit_with_error_message(char *str1, char *str2, char *str3, \
				int32_t exit_value);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

#endif
