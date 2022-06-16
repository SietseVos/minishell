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

enum string_type
{
	SPACE,
	DUPQUOTE,
	SINGLEQUOTE,
};

int32_t	g_exit_status;

typedef struct action_s
{
	char			**arg;
	int32_t			type;
	struct action_s *next;
}	action_t;

typedef struct heredoc_s
{
	char				*str;
	struct env_vars_s	*next;
}	heredoc_t;

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

/* ---------------------------	builtins	------------------------------ */

	int32_t		cd(char **argument, env_vars_t *env);
	int32_t		chdir_error(char *str);
	char		*create_new_cd_str(char *var, char *pwd);
	int32_t		set_oldpwd(env_vars_t *oldpwd_node);
	int32_t		move_pwd_to_oldpwd(env_vars_t *oldpwd_node, env_vars_t *pwd_node, bool *has_been_null);
	int32_t		create_empty_oldpwd(env_vars_t *oldpwd_node, bool *has_been_null);
	void		exit_shell(char **argument, bool print);
	void		pwd(void);
	void		env(env_vars_t *list);
	int32_t		strings_in_array(char **str);
	bool		export(char **args, env_vars_t *env);
	void		bubble_sort_array(char **env_strings, int32_t lst_size);
	int32_t		add_quotes_after_equal(char **strings);
	bool		is_already_in_list(char	*input, env_vars_t *env);
	void		unset(char **arg, env_vars_t **list);
	void		echo(char **args);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* --------------------------	env_functions	-------------------------- */

int32_t			add_env_node(env_vars_t *env, char *str);
bool			create_env_vars_list(char **envp, env_vars_t **env_head);
char			**free_array_till_index(char **array, int32_t index);
void			free_env_list(env_vars_t *list);
char			**env_list_to_array(env_vars_t *env_list);
int32_t			env_list_size(env_vars_t *env_list);
env_vars_t		*get_variable_node(env_vars_t *list, char *variable);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ---------------------------	executer	------------------------------ */

int32_t			executer(action_t *actions, env_vars_t *list);
int32_t			pipe_command(action_t *acts, int32_t fdread, char **envp);
char			*get_executable(char *cmd, char **envp);
int				pplen(char **pp);
void			free_pp(char **pp, int size);
void			pipe_to_file(char **cmd, int32_t fdread, int32_t fdwrite, char **envp);
bool			executer_setup(action_t *acts, env_vars_t *envp);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* -----------------------------	files	------------------------------ */

int32_t			get_infile_fd(action_t	*action);
int32_t			get_outfile_fd(action_t	*action);

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
int32_t			place_str_in_node(char *dst, char *src, int32_t strlen, env_vars_t *envp);
int32_t			place_envvar(char *dst, char *src, env_vars_t *envp, int32_t *i);
action_t		*parse_file(char *input, int32_t *i, env_vars_t *envp);
action_t		*parse_cmd(char *input, int32_t *i, env_vars_t *envp);
int32_t			skipstring(char *str, char quote);
void			read_input_str(char *str, int *strlen, env_vars_t *envp);
action_t		*parser(char *input, env_vars_t *envp);
action_t		*parse_pipe(char *input, int32_t *i);
bool			join_split_cmds(action_t *lst);
bool			merge_nodes(action_t *dst, action_t *src, action_t **prevnextptr);


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

/* ----------------------------------------------------------------------- */

//*************************************************************************//

#endif
