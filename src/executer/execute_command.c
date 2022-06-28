/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 20:51:13 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/27 20:51:15 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function used to call execve and execute a command.
 * 
 * @param arguments Double char array containing all the arguments
 * that will be given to execve,
 * 
 * @param list Pointer to the environment variable list.
 * 
 * @return - [0] Success - [-1] Malloc / execve failed - 
*/
int32_t	execute_command(char **arguments, env_vars_t *list)
{
	char	*execute_path;
	char	**env_array;

	execute_path = get_executable_path(arguments, list);
	if (!execute_path)
		return (-1);
	env_array = env_list_to_array(list);
	if (!env_array)
	{
		free(execute_path);
		return (-1);
	}
	if (execve(execute_path, arguments, env_array) == -1)
	{
		free(execute_path);
		free_double_array(env_array);
		return (-1);
	}
	return (0);
}
