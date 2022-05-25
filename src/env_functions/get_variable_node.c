
#include "minishell.h"

env_vars_t	*get_variable_node(env_vars_t *list, char *variable) // send variable with the included '=' behind it
{
	while (list)
	{
		if (ft_strncmp(variable, list->str, ft_strlen(variable)) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}
