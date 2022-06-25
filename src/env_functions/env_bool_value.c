/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_bool_value.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:50:11 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/25 18:50:43 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	*	Function to check and set if the variable inside the given node
	*	contains a value or not.
	*	@param env Pointer to the environment variable list.
	*	@return N/A
*/
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

/*
	*	Function to set and check if every variable in every node
	*	inside the list has a value attatched to it.
	*	@param env Poiner to the environment variable list.
	*	@return N/A
*/
void	set_env_list_bool_value(env_vars_t *env)
{
	while (env)
	{
		set_env_node_hasvalue(env);
		env = env->next;
	}
}
