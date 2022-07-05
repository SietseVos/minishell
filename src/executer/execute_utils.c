/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 21:20:52 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/05 18:28:46 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to remove nodes till a command node can be found.
 * 
 * @param actions Pointer to the head of the action list.
 * 
 * @return N/A
*/
void	pop_nodes_till_command(t_action **actions)
{
	while (actions && (*actions) && (*actions)->type != TOSTDOUT)
		pop_action_node(actions);
}

/**
 * Function to remove nodes till a pipe node can be found.
 * It will also remove the pipe node itself leaving a new line of
 * nodes ready to be used.
 * 
 * @param actions Pointer to the head of the action list.
 * 
 * @return N/A
*/
void	set_actions_next_pipe(t_action **actions)
{
	while (actions && *actions && (*actions)->type != PIPE)
		pop_action_node(actions);
	if (actions && *actions && (*actions)->type == PIPE)
		pop_action_node(actions);
}

/**
 * Function to check if the action list contains pipes.
 * 
 * @param actions Pointer to the action list.
 * 
 * @return - [true] if there are pipes - [false] if there are no pipes -
*/
bool	contains_pipes(t_action *actions)
{
	while (actions)
	{
		if (actions->type == PIPE)
			return (true);
		actions = actions->next;
	}
	return (false);
}

/**
 * Function to check if the action list contains only builtin commands
 * (no executables or pipes).
 * @param actions Pointer to the action list.
 * 
 * @return - [true] If there are only builtins - [false] if there is more
 * then only builtins -
*/
bool	actions_only_builtins(t_action *actions)
{
	while (actions && actions->type != PIPE)
	{
		if (actions->type == TOSTDOUT
			&& !((ft_strncmp(actions->arg[0], "cd", 3) == 0)
				|| (ft_strncmp(actions->arg[0], "echo", 5) == 0)
				|| (ft_strncmp(actions->arg[0], "env", 4) == 0)
				|| (ft_strncmp(actions->arg[0], "exit", 5) == 0)
				|| (ft_strncmp(actions->arg[0], "export", 7) == 0)
				|| (ft_strncmp(actions->arg[0], "pwd", 4) == 0)
				|| (ft_strncmp(actions->arg[0], "unset", 6) == 0)))
			return (false);
		actions = actions->next;
	}
	return (true);
}

char	*handle_relative_path(char *argument)
{
	char	*cmd_path;

	if (argument[1] == '\0')
	{
		if (argument[0] == '.')
			write(STDERR_FILENO, DOT_ERROR, ft_strlen(DOT_ERROR));
		else
			write(STDERR_FILENO, DIR_ERROR, ft_strlen(DIR_ERROR));
		return (NULL);
	}
	cmd_path = ft_strdup(argument);
	if (!cmd_path)
	{
		write(STDERR_FILENO, "Malloc failed\n", 15);
		return (NULL);
	}
	if (command_found(cmd_path))
		return (cmd_path);
	free(cmd_path);
	write_error_with_strings("minishell: ", argument, \
							": No such file or directory\n");
	return (NULL);
}
