
#include "minishell.h"

int32_t	execute_command(char **arguments, env_vars_t *list)
{
	char	*execute_path;
	char	**env_array;

	execute_path = get_executable_path(arguments, list);
	if (!execute_path)
		return (-1);
	env_array = env_list_to_array(list);
	if (!env_array)
	{
		free(execute_path);
		return (-1);
	}
	if (execve(execute_path, arguments, env_array) == -1)
	{
		free(execute_path);
		free_double_array(env_array);
		return (-1);
	}
	return (-1);
}
