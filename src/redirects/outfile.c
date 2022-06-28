/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   outfile.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 22:01:42 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 22:13:36 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to check if a file exists.
 * If the file exists it will do nothing.
 * If the file does not exist it will create it.
 * 
 * @param path Pointer to the string contaning the path to the file.
 * 
 * @return N/A - exit if close or open fails -
*/
static void	check_if_file_exists(char *path)
{
	int32_t	fd;

	fd = -1;
	if (access(path, F_OK) == -1)
	{
		fd = open(path, O_CREAT);
		if (fd == -1)
			exit_with_error_message("open failed\n", NULL, NULL, 1);
	}
	if (fd != -1)
		if (close(fd) == -1)
			exit_with_error_message("close failed\n", NULL, NULL, 1);
}

/**
 * Function to check if the file has write premissions enabled.
 * 
 * @param path Pointer to the string containing the path of the file.
 * 
 * @return - [true] can write from file - [false] premmission denied -
*/
static int32_t	check_premissions(char *path)
{
	if (access(path, W_OK) == -1)
	{
		write_error_with_strings("minishell: ", path, \
		": Premission denied\n");
		return (false);
	}
	return (true);
}

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
			check_if_file_exists(action->arg[0]);
			if (check_premissions(action->arg[0]) == false)
				return (-1);
			if (action->type == APPEND)
				fd = open(action->arg[0], O_WRONLY | O_APPEND);
			else
				fd = open(action->arg[0], O_WRONLY | O_TRUNC);
			if (fd == -1)
				return (-1);
		}
		action = action->next;
	}
	return (fd);
}
