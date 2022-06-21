/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_variable_node.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:50:50 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/21 21:50:51 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
