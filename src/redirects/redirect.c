/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 22:01:46 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 22:13:47 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int32_t	dup_correct_fd(int32_t (file_function)(t_action *), \
									t_action *actions, int32_t direction)
{
	int32_t	fd;

	fd = file_function(actions);
	if (fd == -2)
		return (-2);
	else if (fd == -1)
		return (-1);
	if (close(direction) == -1)
		exit_with_error_message("close failed\n", NULL, NULL, 1);
	if (dup2(fd, direction) == -1)
		exit_with_error_message("dup2 failed\n", NULL, NULL, 1);
	return (fd);
}

void	reset_redirections(int32_t in_fd, int32_t out_fd)
{
	if (in_fd > 0)
	{
		if (close(in_fd) == -1)
			exit_with_error_message("close failed\n", NULL, NULL, 1);
		if (close(STDIN_FILENO) == -1)
			exit_with_error_message("close failed\n", NULL, NULL, 1);
		if (dup2(STDERR_FILENO, STDIN_FILENO) == -1)
			exit_with_error_message("dup2 failed\n", NULL, NULL, 1);
	}
	if (out_fd > 0)
	{
		if (close(out_fd) == -1)
			exit_with_error_message("close failed\n", NULL, NULL, 1);
		close(STDOUT_FILENO);
		if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
			exit_with_error_message("dup2 failed\n", NULL, NULL, 1);
	}
}

int32_t	set_redirections(t_action *actions, int32_t *in_fd, int32_t *out_fd)
{
	*in_fd = dup_correct_fd(get_infile_fd, actions, STDIN_FILENO);
	if (*in_fd == -1)
		return (-1);
	*out_fd = dup_correct_fd(get_outfile_fd, actions, STDOUT_FILENO);
	if (*out_fd == -1)
	{
		if (*in_fd > 0)
		{
			if (close(*in_fd) == -1)
				exit_with_error_message("close failed\n", NULL, NULL, 1);
			if (dup2(STDERR_FILENO, STDIN_FILENO) == -1)
				exit_with_error_message("dup2 failed\n", NULL, NULL, 1);
		}
		return (-1);
	}
	return (0);
}
