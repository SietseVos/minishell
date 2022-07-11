/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:22:35 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/11 14:27:48 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global_info	g_info;

/**
 * Builtin function to print everything in the environment
 * variable list with a value.
 * 
 * @param list Pointer to the environment variable list.
 * 
 * @return N/A
*/
void	env(t_env_vars *list)
{
	while (list)
	{
		if (list->has_value)
			printf("%s\n", list->str);
		list = list->next;
	}
	g_info.exit_status = 0;
}
