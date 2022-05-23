
#include "minishell.h"

void	add_env_node(env_vars_t *env, char *str)
{
	while (env->next)
	{
		env = env->next;
	}
	env->next = malloc(sizeof(env_vars_t) * 1);
	if (!env->next)
		exit(404);
	env = env->next;
	env->next = NULL;
	env->str = str;
}
