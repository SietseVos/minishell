#ifndef  MINISHELL_H
# define MINISHELL_H
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
# define INFILE 0
# define OUTFILE 1
# define APPEND 2
# define HDOC 3
# define TRUNC 4
# define PIPE 5
# define TOSTDOUT 6
# define NOINPUT 7

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

typedef struct root_s
{
	action_t	*action;
	env_vars_t	*env;
}	root_t;


/* ---------------------------	builtins	------------------------------ */

	void		cd(char **argument, env_vars_t *env);
	void		exit_shell(char **argument);
	void		pwd(void);
	int32_t		strings_in_array(char **str);
	void		export(char **args, env_vars_t *env);
	void		unset(char **arg, env_vars_t **list);
	void		echo(char **args);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* --------------------------	env_functions	-------------------------- */

void			add_env_node(env_vars_t *env, char *str);
void			create_env_vars_list(char **envp, env_vars_t **env_head);
char			**env_list_to_array(env_vars_t *env_list);
int32_t			env_list_size(env_vars_t *env_list);
env_vars_t		*get_variable_node(env_vars_t *list, char *variable);

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

int32_t			strlen_til_space(char *str, int32_t *strlen, env_vars_t *envp);
int32_t			strlen_til_quote(char *str, int32_t *strlen, char c, env_vars_t *envp);
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
int32_t			read_input_str(char *str, int *strlen, env_vars_t *envp);
int32_t			read_input_str(char *str, int *strlen, env_vars_t *envp);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ------------------------------	signals	------------------------------ */

void	init_signals(void);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

#endif
