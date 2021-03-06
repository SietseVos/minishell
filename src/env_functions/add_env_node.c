/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_env_node.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:44:59 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 17:50:04 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to create and set the first node of the env list.
 * 
 * @param head Pointer to the head of the environment variable list.
 * 
 * @param str Pointer to the string that will be set inside the node.
 * 
 * @return - [0] Success - [-1] Malloc failed -
*/
int32_t	set_first_node(t_env_vars **head, char *str)
{
	t_env_vars	*new;

	new = malloc(sizeof(t_env_vars) * 1);
	if (!new)
		return (-1);
	new->next = NULL;
	new->str = str;
	set_env_node_hasvalue(new);
	*head = new;
	return (0);
}

/**
 * Function to add a new environment variable node
 * with the given string to the list.
 * 
 * @param env Pointer to the head of the environment variable list. 
 * 
 * @param str Pointer to the string that will be set inside the node.
 * 
 * @return - [0] Success - [-1] Malloc failed -
*/
int32_t	add_env_node(t_env_vars **env, char *str)
{
	t_env_vars	*new;

	if (!*env)
	{
		if (set_first_node(env, str) == -1)
			return (-1);
		return (0);
	}
	new = *env;
	while (new->next)
		new = new->next;
	new->next = malloc(sizeof(t_env_vars) * 1);
	if (!new->next)
		return (-1);
	new = new->next;
	new->next = NULL;
	new->str = str;
	set_env_node_hasvalue(new);
	return (0);
}
