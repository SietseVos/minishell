
#include "minishell.h"

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
