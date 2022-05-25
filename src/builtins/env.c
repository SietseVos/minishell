
#include "minishell.h"

void	env(env_vars_t *list)
{
	while (list)
	{
		printf("%s\n", list->str);
		list = list->next;
	}
	g_exit_status = 0;
}
