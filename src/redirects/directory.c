/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   directory.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 17:35:07 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/07 20:51:13 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

/**
 * Function to check if the given path is a directory.
 * 
 * @param path Pointer to the string containing the path.
 * 
 * @return - [0] the given path is not a directory -
 * [1] the given path is a directory - [2] the given path does not exist -
*/
int32_t	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (2);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

/**
 * Function to check if the given path is a directory or file.
 * If it is a directory an error message saying so will be printed.
 * If it is a path to a non existent directory or file an error message
 * saying so will be printed.
 * If the premmissions to the given path isnt set according to the
 * premission to check for an error message saying so will be printed.
 * 
 * @param path Pointer to the string containing the path to check.
 * 
 * @param premission The premmision to check for (R_OK, W_OK).
 * 
 * @return - [0] the given string is a path to a file that can be read - 
 * [-1] the given string contains the path to a directory -
*/
int32_t	check_path(char *path, int32_t premission)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		g_info.exit_status = 1;
		write_error_with_strings("minishell: ", path, \
		": No such file or directory\n");
		return (-1);
	}
	if (access(path, premission) == -1)
	{
		g_info.exit_status = 1;
		write_error_with_strings("minishell: ", path, \
		": Premission denied\n");
		return (-1);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		g_info.exit_status = 1;
		write_error_with_strings("minishell: ", path, \
		": Is a directory\n");
		return (-1);
	}
	return (0);
}

/**
 * Function to get the path to the last directory inside a given path.
 * 
 * @param path Pointer to the string containing 
 * 
 * @return - [path] path to the last directory from the given path 
 * - [NULL] malloc failed -
*/
static char	*get_dir_path(char *path)
{
	char		*path_copy;
	int32_t		last_slash;
	int32_t		i;

	i = 0;
	last_slash = 0;
	path_copy = ft_strdup(path);
	if (!path_copy)
	{
		write(2, "Malloc failed\n", 15);
		return (NULL);
	}
	while (path_copy[i])
	{
		if (path_copy[i] == '/')
			last_slash = i;
		i++;
	}
	path_copy[last_slash + 1] = '\0';
	return (path_copy);
}

/**
 * Function to check if a path containing a directory exists
 * and if that directory has write premissions.
 * 
 * @param path Pointer to the string containing the path.
 * 
 * @return - [0] the directory exists and has write premissions -
 * [-1] the directory does not exist or has no write premissions -
*/
static int32_t	check_dir_access(char *path)
{
	struct stat	path_stat;
	char		*dir_path;

	dir_path = get_dir_path(path);
	if (!dir_path)
		return (-1);
	if (stat(dir_path, &path_stat) != 0)
	{
		free(dir_path);
		g_info.exit_status = 1;
		write_error_with_strings("minishell: ", path, \
		": No such file or directory\n");
		return (-1);
	}
	if (access(dir_path, W_OK) == -1)
	{
		free(dir_path);
		g_info.exit_status = 1;
		write_error_with_strings("minishell: ", path, \
		": Premission denied\n");
		return (-1);
	}
	free(dir_path);
	return (0);
}

/**
 * Function to check if the path given is pointing towards a file
 * that may or may not exist and does not point to a directory.
 * Checks for proper access and if it is not a directory itself.
 * 
 * @param path Pointer to the string containing the path to the file.
 * 
 * @return - [0] the path points towards a file that does('nt) exist -
 * [-1] the path points towards a directory or the path is invalid -
*/
int32_t	check_directory(char *path)
{
	struct stat	path_stat;
	int32_t		i;

	i = 0;
	while (path[i] && path[i] != '/')
		i++;
	if (stat(path, &path_stat) != 0)
	{
		if (path[i] == '/' && check_dir_access(path) == -1)
			return (-1);
		return (0);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		g_info.exit_status = 1;
		write_error_with_strings("minishell: ", path, \
		": Is a directory\n");
		return (-1);
	}
	return (0);
}
