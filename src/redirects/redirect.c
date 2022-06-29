/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 22:01:46 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/29 16:51:42 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This function uses the given file function to get an fd and then
 * proceeds to dup that file descriptor to direction.
 * 
 * @param file_function Function to get an fd.
 * 
 * @param actions Pointer to the actions list.
 * 
 * @param direction The file descriptor which will be replaced
 * by the fd recieved from file_function.
 * 
 * @return - [fd] the file descriptor dup2'd to direction -
 * [-2] no file descriptor recieved from file_function -
 * [-1] file function failed -
 * [exit] close / dup2 failed - 
*/
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

/**
 * This function resets the STDIN and STDOUT back to STDERR.
 * 
 * @param in_fd The fd currently used as STDIN.
 * 
 * @param out_fd The fd currently used as STDOUT.
 * 
 * @return - N/A - [exit] close / dup2 failed -
*/
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

/**
 * This function is used to set the STDIN and STDOUT to the
 * corresponding redirects.
 * 
 * @param actions Pointer to the actions list.
 * 
 * @param in_fd Pointer to the int where the new STDIN will be set to.
 * 
 * @param out_fd Pointer to the int where the new STDOUT will be set to.
 * 
 * @return - [0] success - [-1] could get_file function failed -
 * [exit] close / dup2 failed -
*/
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
