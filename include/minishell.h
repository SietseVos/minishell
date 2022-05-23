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
# define TRUNC 0
# define PIPE 1
# define APPEND 2
# define HDOC 3
# define INFILE 4
# define OUTFILE 5

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


/* --------------------------	env_functions	-------------------------- */

void			add_env_node(env_vars_t *env, char *str);
void			create_env_vars_list(char **envp, env_vars_t **env_head);
char			**env_list_to_array(env_vars_t *env_list);

/* ----------------------------------------------------------------------- */

//*************************************************************************//

/* ------------------------------	lexer	------------------------------ */

char			*lexer(char *input);
bool			in_string(char c, bool reset);
char			*check_syntax_error(char *str);

/* ----------------------------------------------------------------------- */

//*************************************************************************//


#endif
