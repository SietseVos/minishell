/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   infile.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 22:01:39 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/08 14:36:52 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

/**
 * Function to handle the ambiguous redirect.
 * This function was created to comply with the norm of functions
 * only containing 25 lines.
 * 
 * @param error_str Pointer to the string containing the ambiguous redirect.
 * 
 * @return - [-1] -
*/
static int32_t	handle_ambiguous_norminette(char *error_str)
{
	g_info.exit_status = 1;
	return (return_with_error_message("minishell: ", \
		error_str, AMBIGU_ERROR, -1));
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
	while (action && action->type != PIPE)
	{
		if (action->type == AMBIGU)
			return (handle_ambiguous_norminette(action->arg[0]));
		if (action->type == INFILE || action->type == HDOCSPACE
			|| action->type == HDOCQUOTE)
		{
			if (fd != -2)
				if (close(fd) == -1)
					exit_with_error_message("close failed\n", NULL, NULL, 1);
			fd = open(action->arg[0], O_RDONLY);
			if (fd == -1)
				return (open_error(action->arg[0], errno));
		}
		action = action->next;
	}
	return (fd);
}
