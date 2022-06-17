
#include "minishell.h"

void	set_env_node_hasvalue(env_vars_t *env)
{
	int32_t	i;

	i = 0;
	if (env)
	{
		env->has_value = false;
		while (env->str[i])
		{
			if (env->str[i] == '=')
				env->has_value = true;
			i++;
		}
	}

}

void	set_env_list_bool_value(env_vars_t *env)
{
	while (env)
	{
		set_env_node_hasvalue(env);
		env = env->next;
	}
}
