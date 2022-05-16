
#ifndef  MINISHELL_H
# define MINISHELL_H

typedef struct action_s
{
	int				input_fd;
	int				output_fd;
	char			*command;
	char			*argument;
	struct action_s *next;
}	action_t;

typedef struct root_s
{
	action_t	**action_head;
}	root_t;

#endif
