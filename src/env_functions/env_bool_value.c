/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_bool_value.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:50:11 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/21 21:50:21 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
