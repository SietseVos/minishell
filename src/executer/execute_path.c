/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 20:52:21 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/27 21:22:37 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to check if a command can be found and if the
 * premmisions are there to execute it.
 * 
 * @param path Pointer to the string containing the path to the command.
 * 
 * @return - [true] if executable can be found - 
 * [false] executable can't be found -
*/
static bool	command_found(const char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (true);
		else
			write_error_with_strings("minishell: ", (char *)path, \
						": Premission denied\n");
		return (true);
	}
	return (false);
}

/**
 * Function to copy the command behind the path
 * inside of a new string, with a '/' added in between.
 * 
 * @param path Pointer to the string containing the path.
 * 
 * @param command Pointer to the string containing the name of the executable.
 * 
 * @return The new string containing
 * the path and command with a '/' in between.
*/
static char	*set_command_after_path(const char *path, const char *command)
{
	int32_t	new_str_len;
	char	*new_str;

	new_str_len = ft_strlen(path) + ft_strlen(command) + 2;
	new_str = ft_calloc(new_str_len, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcat(new_str, path, new_str_len);
	ft_strlcat(new_str, "/", new_str_len);
	ft_strlcat(new_str, command, new_str_len);
	return (new_str);
}

/**
 * Function to find an executable within the PATH variable.
 * 
 * @param arguments Double char array containing the name of the executable.
 * 
 * @param path Pointer to the environment variable node contaiing
 * the PATH variable.
 * 
 * @return - [execute_path] Path of the executable if it can be found -
 * [NULL] If there isnt an executable with the same name within the
 * PATH variable -
*/
static char	*norminette_wants_this_to_be_split(char **arguments, \
		env_vars_t *path)
{
	char	**all_paths;
	char	*execute_path;
	int32_t	i;

	i = 0;
	all_paths = ft_split(path->str, ':');
	if (!all_paths)
		return (NULL);
	while (all_paths[i])
	{
		execute_path = set_command_after_path(all_paths[i], arguments[0]);
		if (!execute_path)
			break ;
		if (command_found(execute_path))
		{
			free_double_array(all_paths);
			return (execute_path);
		}
		free(execute_path);
		i++;
	}
	free_double_array(all_paths);
	return (NULL);
}

/**
 * Function to get the path of an executable within the PATH
 * environment variable.
 * 
 * @param arguments Double char array containing the name of the executable.
 * 
 * @param list Pointer to the environment variable list.
 * 
 * @return - [execute_path] Path of the executable if it can be found -
 * [NULL] If there isnt an executable with the same name within the
 * PATH variable -
*/
static char	*find_command_in_path(char **arguments, env_vars_t *list)
{
	env_vars_t	*path;

	path = get_variable_node(list, "PATH=");
	if (!path)
		return (NULL);
	return (norminette_wants_this_to_be_split(arguments, path));
}

/**
 * Function to get the path of the executable, wether it is in the
 * environment variable PATH or if it is a relative path.
 * If the executable can't be found an error will be printed.
 * 
 * @param arguments Double char array containing the name of the executable.
 * 
 * @param list Pointer to the environment variable list.
 * 
 * @return - [execute_path] Path of the executable if it can be found -
 * [NULL] If there isnt an executable that can be found -
*/
char	*get_executable_path(char **arguments, env_vars_t *list)
{
	char	*cmd_path;

	if (!arguments || !arguments[0])
		return (NULL);
	cmd_path = find_command_in_path(arguments, list);
	if (cmd_path)
		return (cmd_path);
	else
	{
		cmd_path = ft_strdup(arguments[0]);
		if (command_found(cmd_path))
			return (cmd_path);
		free(cmd_path);
	}
	write_error_with_strings("minishell: ", arguments[0], \
									": command not found\n");
	return (NULL);
}
