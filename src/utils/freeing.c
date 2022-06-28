#include "minishell.h"

bool	free_env_list_return_false(t_env_vars *env)
{
	t_env_vars	*tmp;
	t_env_vars	*next;

	tmp = env;
	while (tmp)
	{
		if (tmp->str)
			free(tmp->str);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	return (false);
}

void	free_double_array(char **array)
{
	int32_t	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	free_env_list(t_env_vars *list)
{
	t_env_vars	*tmp;
	t_env_vars	*next;

	tmp = list;
	while (tmp)
	{
		if (tmp->str)
			free(tmp->str);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	pop_action_node(t_action **node)
{
	t_action	*next;

	if (!node || !*node)
		return ;
	free_double_array((*node)->arg);
	next = (*node)->next;
	free((*node));
	*node = next;
}

void	free_action_list(t_action **node)
{
	while (node && *node)
		pop_action_node(node);
}
