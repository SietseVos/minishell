/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_variable_node.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:50:50 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/25 19:01:36 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	*	Function to check if the given string contains the same variable
	*	as the given variable.
	*	@param str Pointer to the string to compare to.
	*	@param var Pointer to the string to check if its the same.
	*	@return - [1] Strings contain the same variable -
	*	[0] Strings so not contain the same variable -
*/
static int32_t	compare_var_in_list(char *str, char *var)
{
	int32_t	i;

	i = 0;
	while (str[i] && var[i] && var[i] != '=' && (str[i] == var[i]))
		i++;
	if ((str[i] == '=' && var[i] == '=') || (str[i] == '\0' && var[i] == '\0')
		|| (str[i] == '=' && var[i] == '\0'))
		return (0);
	return (1);
}

/*
	*	Function to get an environment variable node that contains the
	*	given variable.
	*	@param list Pointer to the environment variable list. 
	*	@param variable Pointer to the string containing the variable to search for.
	*	@return - [list] Node containing the variable - 
	*	[NULL] List does not contain the given variable.
*/
env_vars_t	*get_variable_node(env_vars_t *list, char *variable)
{
	while (list)
	{
		if (compare_var_in_list(list->str, variable) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}
