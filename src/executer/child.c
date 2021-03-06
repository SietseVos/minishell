/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 20:51:21 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 17:50:27 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

/**
 * Function to exit the program with the golbal exit status,
 * close the given fd and reset the redirections/dup2 back to
 * the terminal.
 * 
 * @param infile_fd fd of the infile which has to be closed. 
 * 
 * @param outfile_fd fd of the oufile which has to be closed.
 * 
 * @param fd_in fd wfrom the pipe which has to be closed.
 * 
 * @return Exits
*/
static void	exit_and_close_fds(int32_t infile_fd, \
						int32_t outfile_fd, int32_t fd_in)
{
	if (close(fd_in) == -1)
		exit_with_error_message("close failed\n", NULL, NULL, 1);
	reset_redirections(infile_fd, outfile_fd);
	exit (g_info.exit_status);
}

/**
 * Function to run inside of a fork and call execve or the
 * builtin function.
 * 
 * @param info Struct containing the actions and environment variables.
 * 
 * @param fd Pointer to the pipe that has to be used if it is there.
 * 
 * @param fd_in The fd to be used as stdin.
 * 
 * @param contains_pipes Boolian that shows if there is a pipe to be used.
 * 
 * @return Exits
*/
void	run_child(t_info info, int32_t *fd, int32_t fd_in, bool contains_pipes)
{
	int32_t	infile_fd;
	int32_t	outfile_fd;

	signal(SIGINT, SIG_DFL);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit_with_error_message("dup2 failed\n", NULL, NULL, 1);
	if (contains_pipes)
	{
		if (close(fd[PIPE_READ]) == -1)
			exit_with_error_message("close failed\n", NULL, NULL, 1);
		if (dup2(fd[PIPE_WRITE], STDOUT_FILENO) == -1)
			exit_with_error_message("dup2 failed\n", NULL, NULL, 1);
	}
	if (set_redirections((*info.action), &infile_fd, &outfile_fd) == -1)
		exit (1);
	pop_nodes_till_command(info.action);
	if (!(*info.action))
		exit_and_close_fds(infile_fd, outfile_fd, fd_in);
	else if (run_if_builtin_child(info))
		exit_and_close_fds(infile_fd, outfile_fd, fd_in);
	execute_command((*info.action)->arg, (*info.list));
	exit_and_close_fds(infile_fd, outfile_fd, fd_in);
}
