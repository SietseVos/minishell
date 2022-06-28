/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_builtins.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:02:35 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 17:08:17 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to compare the first string inside the first action node with
 * all the supported builtins and execute it if it is found.
 * 
 * @param info Struct contaning the action list and environment
 * variable list.
 * 
 * @return - [true] builtin found and executed - [false] builtin not found -
*/
bool	run_if_builtin_child(info_t info) // check if cd or export fails?
{
	if (ft_strncmp((*info.action)->arg[0], "cd", 3) == 0)
		cd(&(*info.action)->arg[1], info.list);
	else if (ft_strncmp((*info.action)->arg[0], "echo", 5) == 0)
		echo(&(*info.action)->arg[1]);
	else if (ft_strncmp((*info.action)->arg[0], "env", 4) == 0)
		env((*info.list));
	else if (ft_strncmp((*info.action)->arg[0], "exit", 5) == 0)
		exit_shell(&(*info.action)->arg[1], false);
	else if (ft_strncmp((*info.action)->arg[0], "export", 7) == 0)
		export(&(*info.action)->arg[1], info.list);
	else if (ft_strncmp((*info.action)->arg[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp((*info.action)->arg[0], "unset", 6) == 0)
		unset(&(*info.action)->arg[1], info.list);
	else
		return (false);
	return (true);
}

/**
 * Funtion to run a builtin, will clear the action list till it finds a
 * node containing the command.
 * 
 * @param actions Pointer to the head of the action list.
 * 
 * @param list Pointer to the head of the environment variable list.
 * 
 * @return - [0] no builtins found or builtin ran without issues -
 * [-1] builtin (cd or export) encountered an issue -
*/
int32_t	run_builtin_no_pipe(action_t **actions, env_vars_t **list)
{
	int32_t		return_value;

	return_value = 0;
	pop_nodes_till_command(actions);
	if (!actions || !*actions)
		return (0);
	if (ft_strncmp((*actions)->arg[0], "cd", 3) == 0)
		return_value = cd(&(*actions)->arg[1], list);
	else if (ft_strncmp((*actions)->arg[0], "echo", 5) == 0)
		echo(&(*actions)->arg[1]);
	else if (ft_strncmp((*actions)->arg[0], "env", 4) == 0)
		env(*list);
	else if (ft_strncmp((*actions)->arg[0], "exit", 5) == 0)
		exit_shell(&(*actions)->arg[1], true);
	else if (ft_strncmp((*actions)->arg[0], "export", 7) == 0)
		return_value = export(&(*actions)->arg[1], list);
	else if (ft_strncmp((*actions)->arg[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp((*actions)->arg[0], "unset", 6) == 0)
		unset(&(*actions)->arg[1], list);
	if (return_value == -1)
		return (-1);
	return (0);
}
