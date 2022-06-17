
#include "minishell.h"

static bool	command_found(const char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (true);
		else
			printf("bash: %s: Premission denied\n", path);
		return (false);
	}
	return (false);
}

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

static char	*find_command_in_path(char **arguments, env_vars_t *list)
{
	env_vars_t	*path;

	path = get_variable_node(list, "PATH=");
	if (!path)
		return (NULL);
	return (norminette_wants_this_to_be_split(arguments, path));
}

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
	printf("bash: %s: command not found\n", arguments[0]);
	return (NULL);
}
