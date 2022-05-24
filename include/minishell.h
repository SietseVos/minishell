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
	int				type;
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
	int			strings_in_array(char **str);

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
void			skip_string(char *str, int *i);
bool			check_syntax_error(char *str);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ------------------------------	parser	------------------------------ */

int				strlen_til_space(char *str, int *strlen, char **envp);
void			*nullerr(char *errmsg);
int				is_operator(char c);
int				check_str_end(char *str, int i, int n);
int				strlen_til_quote(char *str, int *strlen, char c, char **envp);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

#endif
