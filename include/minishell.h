#ifndef  MINISHELL_H
# define MINISHELL_H
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
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


typedef struct root_s
{
	action_t	*action_head;
}	root_t;

#endif
