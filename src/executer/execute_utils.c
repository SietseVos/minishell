
#include "minishell.h"

void	pop_nodes_till_command(action_t **actions)
{
	while (actions && (*actions) && (*actions)->type != TOSTDOUT)
		pop_action_node(actions);
}

void	set_actions_next_pipe(action_t **actions)
{
	while (actions && *actions &&(*actions)->type != PIPE)
		pop_action_node(actions);
	if (actions && *actions &&(*actions)->type == PIPE)
		pop_action_node(actions);
}

bool	contains_pipes(action_t *actions)
{
	while (actions)
	{
		if (actions->type == PIPE)
			return (true);
		actions = actions->next;
	}
	return (false);
}

bool	actions_only_builtins(action_t *actions) 
{
	while (actions && actions->type != PIPE)
	{
		if (actions->type == TOSTDOUT
			&& !((ft_strncmp(actions->arg[0], "cd", 3) == 0)
			|| (ft_strncmp(actions->arg[0], "echo", 5) == 0)
			|| (ft_strncmp(actions->arg[0], "env", 4) == 0)
			|| (ft_strncmp(actions->arg[0], "exit", 5) == 0)
			|| (ft_strncmp(actions->arg[0], "export", 7) == 0)
			|| (ft_strncmp(actions->arg[0], "pwd", 4) == 0)
			|| (ft_strncmp(actions->arg[0], "unset", 6) == 0)))
			return (false);
		actions = actions->next;
	}
	return (true);
}
