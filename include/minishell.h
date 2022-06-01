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

// legacy code
#define ruben int8_t 	// this was orginally used as a solution to a complitaced problem ruben (cat), ruben (the best) and int32_t encouncered during their adventures in minihell
#define sietse int32_t	// sietse also wanted to feel special so we made him a data type aswell :)

enum type
{
	INFILE,
	OUTFILE,
	APPEND,
	HDOC,
	TRUNC,
	PIPE,
	TOSTDOUT,
	NOINPUT,
	INPIPE
};

int32_t	g_exit_status;

typedef struct action_s
{
	char			**arg;
	int32_t			type;
	struct action_s *next;
}	action_t;

typedef struct env_vars_s
{
	char				*str;
	struct env_vars_s	*next;
}	env_vars_t;

/* ---------------------------	builtins	------------------------------ */

	int32_t		cd(char **argument, env_vars_t *env);
	void		exit_shell(char **argument);
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

void	execute(action_t *actions, env_vars_t *list);

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

void			strlen_til_space(char *str, int32_t *strlen, env_vars_t *envp);
void			strlen_til_quote(char *str, int32_t *strlen, char c, env_vars_t *envp);
int32_t			strlen_quote(char *str);
int32_t			envvarlen(char *str, char end);
void			*nullerr(char *errmsg);
int32_t			is_operator(char c);
int32_t			check_str_end(char *str, int32_t i, int32_t n);
void			printenvp(env_vars_t *print);
int32_t			place_str_in_node(char *dst, char *src, int32_t strlen, env_vars_t *envp);
int32_t			place_envvar(char *dst, char *src, env_vars_t *envp, int32_t *i);
action_t		*parse_file(char *input, int32_t *i, env_vars_t *envp);
action_t		*parse_cmd(char *input, int32_t *i, env_vars_t *envp);
int32_t			skipstring(char *str, char quote);
void			read_input_str(char *str, int *strlen, env_vars_t *envp);
action_t		*parser(char *input, env_vars_t *envp);


void	print_actions(action_t *inlst);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ------------------------------	signals	------------------------------ */

void	init_signals(void);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

#endif
