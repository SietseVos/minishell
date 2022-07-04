/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_variable_node.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:50:50 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 17:50:04 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to check if the given string contains the same variable
 * as the given variable.
 * 
 * @param str Pointer to the string inside the node to compare against.
 * @param var Pointer to the string to check if its the same.
 * 
 * @return - [0] Strings contain the same variable -
 * [1] Strings so not contain the same variable -
*/
static int32_t	compare_var_in_list(char *str, char *var)
{
	int32_t	i;

	i = 0;
	while (str[i] && var[i] && var[i] != '=' && (str[i] == var[i]))
		i++;
	if (var[i] == '+' && var[i + 1] == '=' && \
		(str[i] == '=' || str[i] == '\0'))
		return (0);
	if ((str[i] == '=' && var[i] == '=') 
		|| (str[i] == '\0' && var[i] == '\0')
		|| (str[i] == '=' && var[i] == '\0'))
		return (0);
	return (1);
}

/**
 * Function to get an environment variable node that contains the
 * given variable.
 * 
 * @param list Pointer to the environment variable list. 
 * @param variable Pointer to the string containing the variable to search for.
 * 
 * @return - [list] Node containing the variable - 
 * [NULL] List does not contain the given variable.
*/
t_env_vars	*get_variable_node(t_env_vars *list, char *variable)
{
	while (list)
	{
		if (compare_var_in_list(list->str, variable) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}
