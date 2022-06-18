
#include "minishell.h"

int32_t	add_env_node(env_vars_t *env, char *str)
{
	while (env->next)
	{
		env = env->next;
	}
	env->next = malloc(sizeof(env_vars_t) * 1);
	if (!env->next)
		return (-1);
	env = env->next;
	env->next = NULL;
	env->str = str;
	set_env_node_hasvalue(env);
	return (0);
}
