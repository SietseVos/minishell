/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   infile.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 22:01:39 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/27 14:22:43 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	access_error(action_t *action)
{
	while (action && action->type != PIPE)
	{
		if (action->type == INFILE || action->type == HDOC)
		{
			if (access(action->arg[0], F_OK) == -1)
			{
				g_exit_status = 1;
				write_error_with_strings("bash: ", action->arg[0], \
				": No such file or directory\n");
				return (true);
			}
			else if (access(action->arg[0], R_OK) == -1)
			{
				g_exit_status = 1;
				write_error_with_strings("bash: ", action->arg[0], \
				": Premission denied\n");
				return (true);
			}
		}
		action = action->next;
	}
	return (false);
}

int32_t	get_infile_fd(action_t	*action)
{
	int32_t	fd;

	fd = -2;
	if (access_error(action))
		return (-1);
	while (action && action->type != PIPE)
	{
		if (action->type == INFILE || action->type == HDOCSPACE
			|| action->type == HDOCQUOTE)
		{
			if (fd != -2)
				close(fd);
			fd = open(action->arg[0], O_RDONLY);
			if (fd == -1)
				return (-1);
		}
		action = action->next;
	}
	return (fd);
}
