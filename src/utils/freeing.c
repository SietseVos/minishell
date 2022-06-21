#include "minishell.h"

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

void	free_env_list(env_vars_t *list)
{
	env_vars_t	*tmp;
	env_vars_t	*next;

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

void	pop_action_node(action_t **node)
{
	action_t	*next;

	if (!node || !*node)
		return ;
	free_double_array((*node)->arg);
	next = (*node)->next;
	free((*node));
	*node = next;
}

void	free_action_list(action_t **node)
{
	while (node && *node)
		pop_action_node(node);
}
