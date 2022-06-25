/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_env_vars_list.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:49:43 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/25 18:47:34 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	*	Function to create a new environment variable node with a given value.
	*	@param envp Pointer to the string containing the value to be copied
	*	into the new node.
	*	@return - [new] Pointer to the newly created node - [NULL] Malloc failed -
*/
static env_vars_t	*new_env_node(char *envp)
{
	env_vars_t	*new;

	new = malloc(sizeof(env_vars_t));
	if (!new)
		return (NULL);
	new->str = ft_strdup(envp);
	if (!new->str)
	{
		free (new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

/*
	*	Function to create the environment variable list.
	*	@param envp Double char array containing the intormation
	*	which has to be converted to the linked list.
	*	@param env_head Pointer to the locaiton of the head of
	*	the environment variable list.
	*	@return - [true] Success - [false] Malloc failed - 
*/
bool	create_env_vars_list(char **envp, env_vars_t **env_head)
{
	env_vars_t	*tmp;
	env_vars_t	*new;
	int32_t		i;

	i = 0;
	while (envp[i])
	{
		new = new_env_node(envp[i]);
		if (!new)
			return (free_env_list_return_false(*env_head));
		if (i == 0)
		{
			tmp = new;
			*env_head = tmp;
			i++;
			continue ;
		}
		else
			tmp->next = new;
		tmp = tmp->next;
		i++;
	}
	return (clean_env_vars_list(env_head));
}
