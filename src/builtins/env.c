/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:22:35 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/27 20:34:42 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Builtin function to print everything in the environment
 * variable list with a value.
 * 
 * @param list Pointer to the environment variable list.
 * 
 * @return N/A
*/
void	env(env_vars_t *list)
{
	while (list)
	{
		if (list->has_value)
			printf("%s\n", list->str);
		list = list->next;
	}
	g_exit_status = 0;
}
