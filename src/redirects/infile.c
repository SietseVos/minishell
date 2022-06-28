/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   infile.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 22:01:39 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 22:04:50 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Funtion to check if the action nodes contains a files
 * that can be opened or not. If the file can't be opened it
 * will display an error message.
 * 
 * @param action Pointer to the action node list.
 * 
 * @return - [true] can't access a file - [false] all files can be accessed - 
*/
static bool	access_error(t_action *action)
{
	while (action && action->type != PIPE)
	{
		if (action->type == INFILE || action->type == HDOCSPACE
			|| action->type == HDOCQUOTE)
		{
			if (access(action->arg[0], F_OK) == -1)
			{
				g_info.exit_status = 1;
				write_error_with_strings("minishell: ", action->arg[0], \
				": No such file or directory\n");
				return (true);
			}
			else if (access(action->arg[0], R_OK) == -1)
			{
				g_info.exit_status = 1;
				write_error_with_strings("minishell: ", action->arg[0], \
				": Premission denied\n");
				return (true);
			}
		}
		action = action->next;
	}
	return (false);
}

/**
 * Function to get the last file descriptor in the list.
 * It will open all other infiles as it is going past them.
 * 
 * @param action Pointer to the action list.
 * 
 * @return - [fd] file descriptor of the last infile/heredoc -
 * [-1] access or open fail -
*/
int32_t	get_infile_fd(t_action	*action)
{
	int32_t	fd;

	fd = -2;
	if (access_error(action))
		return (-1);
	while (action && action->type != PIPE)
	{
		if (action->type == AMBIGU)
		{
			g_info.exit_status = 1;
			return (return_with_error_message("minishell: ", \
								action->arg[0], AMBIGU_ERROR, -1));
		}
		if (action->type == INFILE || action->type == HDOCSPACE
			|| action->type == HDOCQUOTE)
		{
			if (fd != -2)
				if (close(fd) == -1)
					exit_with_error_message("close failed\n", NULL, NULL, 1);
			fd = open(action->arg[0], O_RDONLY);
			if (fd == -1)
				return (-1);
		}
		action = action->next;
	}
	return (fd);
}
