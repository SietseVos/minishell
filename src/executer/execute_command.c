/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 20:51:13 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/08 15:44:37 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>
#include <errno.h>

/**
 * Function to check if the given path points towards a direcory or not.
 * 
 * @param path Pointer to the string containg the path to check for a dir.
 * 
 * @return - [true] path points towards a directory
 * - [false] path does not point towards a directory -
*/
static bool	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	if (S_ISDIR(path_stat.st_mode))
		return (true);
	return (false);
}

/**
 * Function to display the encountered error with the execve function
 * and exit with the right exit value.
 * 
 * @param path Pointer to the string containing the path to the executable.
 * 
 * @param error The errno that execve set.
 * 
 * @return - [exit 126] the given path is a directory
 * - [exit 127] other errors - 
*/
static void	execve_error(char *path, int32_t error)
{
	if (error == EACCES)
	{
		if (is_directory(path))
		{
			write_error_with_strings("minishell: ", path, \
			": is a directory\n");
			exit (126);
		}
		else
			write_error_with_strings("minishell: ", path, \
			": Premission denied\n");
	}
	else if (error == ENOENT)
		write_error_with_strings("minishell: ", path, \
		": command not found\n");
	else
		write_error_with_strings("minishell: ", path, \
		": execve error\n");
	exit (127);
}

/**
 * Function used to call execve and execute a command.
 * 
 * @param arguments Double char array containing all the arguments
 * that will be given to execve,
 * 
 * @param list Pointer to the environment variable list.
 * 
 * @return - [0] Success - [-1] Malloc / execve failed -
 * [exit 127] command not found -
*/
int32_t	execute_command(char **arguments, t_env_vars *list)
{
	char	*execute_path;
	char	**env_array;

	execute_path = get_executable_path(arguments, list);
	if (!execute_path)
		exit (127);
	env_array = env_list_to_array(list);
	if (!env_array)
	{
		free(execute_path);
		return (return_with_error_message("Malloc failed\n", NULL, NULL, -1));
	}
	if (execve(execute_path, arguments, env_array) == -1)
		execve_error(execute_path, errno);
	return (0);
}
