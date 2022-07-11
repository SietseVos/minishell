/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   outfile.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 22:01:42 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/08 19:05:43 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

/**
 * Function to get the fd of the file which has to be written to.
 * 
 * @param action Pointer to the action list.
 * 
 * @return - [fd] the file descriptor of the outfile - 
 * [-1] open failed - [exit] close failed -
*/
int32_t	get_outfile_fd(t_action	*action)
{
	int32_t	fd;

	fd = -2;
	while (action && action->type != PIPE)
	{
		if (action->type == TRUNC || action->type == APPEND)
		{
			if (fd != -2)
			{
				if (close(fd) == -1)
					exit_with_error_message("close failed\n", NULL, NULL, 1);
			}
			if (action->type == APPEND)
				fd = open(action->arg[0], O_CREAT | O_WRONLY | O_APPEND, 0666);
			else
				fd = open(action->arg[0], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (fd == -1)
				return (open_error(action->arg[0], errno));
		}
		action = action->next;
	}
	return (fd);
}
