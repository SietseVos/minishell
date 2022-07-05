/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_trash.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 14:48:41 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/05 13:49:10 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function that can be used to close the given pipe and file descriptor.
 * 
 * @param pipe_fds Pointer to the array cointaining fds from a single pipe.
 * 
 * @param fd_in Integer containing the file descriptor used as infile.
 * 
 * @return - [-1] -
*/
int32_t	close_fds_and_return(int32_t *pipe_fds, int32_t fd_in)
{
	if (pipe_fds)
	{
		if (close(pipe_fds[0]) == -1)
			exit_with_error_message("close failed\n", NULL, NULL, 1);
		if (close(pipe_fds[1]) == -1)
			exit_with_error_message("close failed\n", NULL, NULL, 1);
	}
	if (close(fd_in) == -1)
		exit_with_error_message("close failed\n", NULL, NULL, 1);
	return (-1);
}

/**
 * Function to close the fds set inside the run_with_pipes function.
 * If close fails the program will exit.
 * 
 * @param close_pipe If set to true the write side of
 * the pipe_fds will be closed.
 * 
 * @param fd_in If its bigger then 0 this function will attempt to close it.
 * 
 * @param pipe_fds Pointer to the array of fds created by a pipe.
 * 
 * @return - N/A - exit on close fail -
*/
void	close_fds_run_with_pipes(bool close_pipe, int32_t fd_in, \
													int32_t *pipe_fds)
{
	if (fd_in > 0)
	{
		if (close(fd_in) == -1)
			exit_with_error_message("close failed\n", NULL, NULL, 1);
	}
	if (close_pipe && close(pipe_fds[PIPE_WRITE]) == -1)
		exit_with_error_message("close failed\n", NULL, NULL, 1);
}
