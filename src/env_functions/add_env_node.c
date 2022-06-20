
#include "minishell.h"

int32_t	set_first_node(env_vars_t **head, char *str)
{
	env_vars_t	*new;

	new = malloc(sizeof(env_vars_t) * 1);
	if (!new)
		return (-1);
	new->next = NULL;
	new->str = str;
	set_env_node_hasvalue(new);
	*head = new;
	return (0);
}

int32_t	add_env_node(env_vars_t **env, char *str)
{
	env_vars_t	*new;

	if (!*env)
	{
		if (set_first_node(env, str) == -1)
			return (-1);
		return (0);
	}
	new = *env;
	while (new->next)
		new = new->next;
	new->next = malloc(sizeof(env_vars_t) * 1);
	if (!new->next)
		return (-1);
	new = new->next;
	new->next = NULL;
	new->str = str;
	set_env_node_hasvalue(new);
	return (0);
}
