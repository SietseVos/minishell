/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   freeing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 15:01:03 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/05 15:07:19 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to free the environment variable list and return false.
 * 
 * @param env Pointer to the head of the environment variable list.
 * 
 * @return - [false] -
*/
bool	free_env_list_return_false(t_env_vars **env)
{
	t_env_vars	*tmp;
	t_env_vars	*next;

	tmp = *env;
	while (tmp)
	{
		if (tmp->str)
			free(tmp->str);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*env = NULL;
	return (false);
}

/**
 * Function to free a double character array.
 * 
 * @param array Pointer to the double character array.
 * 
 * @return - N/A -
*/
void	free_double_array(char **array)
{
	int32_t	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

/**
 * Function to remove the first action node and set the head to the next node.
 * 
 * @param node Pointer to the head of the action list.
 * 
 * @return - N/A -
*/
void	pop_action_node(t_action **node)
{
	t_action	*next;

	if (!node || !*node)
		return ;
	free_double_array((*node)->arg);
	next = (*node)->next;
	free((*node));
	*node = next;
}

/**
 * Function to free the entire action list.
 * 
 * @param node Pointer to the head of the action list.
 * 
 * @return - N/A -
*/
void	free_action_list(t_action **node)
{
	while (node && *node)
		pop_action_node(node);
}
