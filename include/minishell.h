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
	void		pwd(char **argument);
	int32_t		strings_in_array(char **str);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* --------------------------	env_functions	-------------------------- */

void			add_env_node(env_vars_t *env, char *str);
void			create_env_vars_list(char **envp, env_vars_t **env_head);
char			**env_list_to_array(env_vars_t *env_list);

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
void			*nullerr(char *errmsg);
int32_t			is_operator(char c);
int32_t			check_str_end(char *str, int32_t i, int32_t n);
int32_t			strlen_til_quote(char *str, int32_t *strlen, char c, env_vars_t *envp);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

#endif
