/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   infile.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 22:01:39 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 16:59:58 by rvan-mee      ########   odam.nl         */
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
				g_info.exit_status = 1;
				write_error_with_strings("bash: ", action->arg[0], \
				": No such file or directory\n");
				return (true);
			}
			else if (access(action->arg[0], R_OK) == -1)
			{
				g_info.exit_status = 1;
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
			{
				if (close(fd) == -1)
					exit_with_error_message("close failed\n", NULL, NULL, 1);
			}
			fd = open(action->arg[0], O_RDONLY);
			if (fd == -1)
				return (-1);
		}
		action = action->next;
	}
	return (fd);
}
