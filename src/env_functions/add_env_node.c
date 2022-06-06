
#include "minishell.h"

int32_t	add_env_node(env_vars_t *env, char *str)
{
	int32_t	i;

	i = 0;
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
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		env->has_value = true;
	else
		env->has_value = false;
	return (0);
}
