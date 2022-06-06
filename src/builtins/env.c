
#include "minishell.h"

void	env(env_vars_t *list)
{
	while (list)
	{
		if (list->has_value)
			printf("%s\n", list->str);
		list = list->next;
	}
	g_exit_status = 0;
}
