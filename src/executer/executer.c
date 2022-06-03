
#include "minishell.h"

static void	free_action_list(action_t **actions)
{
	action_t	*next;
	action_t	*remove;

	remove = *actions;
	while (remove)
	{
		next = remove->next;
		free_array_till_index(remove->arg, strings_in_array(remove->arg) + 1);
		free(remove);
		remove = next;
	}
	*actions = NULL;
}

static void	free_double_array(char **array)
{
	int32_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
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

static bool	command_found(const char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return (true);
	return (false);
}

static int32_t	find_command_and_execute(char **arguments, env_vars_t *list)
{
	env_vars_t	*path;
	char		**all_paths;
	char		**env_array;
	char		*execute_path;
	int32_t		i;

	i = 0;
	path = get_variable_node(list, "PATH=");
	if (!path)
		return (0);
	all_paths = ft_split(path->str, ':');
	if (!all_paths)
		return (-1);
	while (all_paths[i])
	{
		execute_path = set_command_after_path(all_paths[i], arguments[0]);
		if (!execute_path)
		{
			free_double_array(all_paths);
			return (-1);
		}
		else if (command_found(execute_path))
		{
			free_double_array(all_paths);
			env_array = env_list_to_array(list);
			if (!env_array)
			{
				free(execute_path);
				return (-1);
			}
			if (execve(execute_path, arguments, env_array) == -1)
			{
				free_double_array(env_array);
				free(execute_path);
				return (-1);
			}
			free_double_array(env_array);
			free(execute_path);
			return (1);
		}
		free(execute_path);
		i++;
	}
	return (0);
}

bool	actions_contain_pipe(action_t *actions)
{
	while (actions)
	{
		if (actions->type == PIPE)
			return (true);
		actions = actions->next;
	}
	return (false);
}

bool	actions_only_builtins(action_t *actions) // check ytpe 
{
	while (actions)
	{
		if (!((ft_strncmp(actions->arg[0], "cd", 3) == 0)
			|| (ft_strncmp(actions->arg[0], "echo", 5) == 0)
			|| (ft_strncmp(actions->arg[0], "env", 4) == 0)
			|| (ft_strncmp(actions->arg[0], "exit", 5) == 0)
			|| (ft_strncmp(actions->arg[0], "export", 7) == 0)
			|| (ft_strncmp(actions->arg[0], "pwd", 4) == 0)
			|| (ft_strncmp(actions->arg[0], "unset", 6) == 0)))
			return (false);
		actions = actions->next;
	}
	return (true);
}

void	execute(action_t *actions, env_vars_t *list)
{
	bool		return_value_b;
	int32_t		return_value_i;
	action_t	*start;

	start = actions;
	while (actions)
	{
		return_value_i = 0;
		return_value_b = true;
		if (ft_strncmp(actions->arg[0], "cd", 3) == 0)
			return_value_i = cd(&actions->arg[1], list);
		else if (ft_strncmp(actions->arg[0], "echo", 5) == 0)
			echo(&actions->arg[1]);
		else if (ft_strncmp(actions->arg[0], "env", 4) == 0)
			env(list);
		else if (ft_strncmp(actions->arg[0], "exit", 5) == 0)
		{
			free_env_list(list);
			exit_shell(&actions->arg[1]);
		}
		else if (ft_strncmp(actions->arg[0], "export", 7) == 0)
			return_value_b = export(&actions->arg[1], list);
		else if (ft_strncmp(actions->arg[0], "pwd", 4) == 0)
			pwd();
		else if (ft_strncmp(actions->arg[0], "unset", 6) == 0)
			unset(&actions->arg[1], &list);
		else if (find_command_and_execute(actions->arg, list) == 0)
			printf("bash: %s: command not found\n", actions->arg[0]);
		if (return_value_i == -1 || return_value_b == false)
		{
			printf("malloc error!\n");
			exit(404);
		}
		actions = actions->next;
		// system("leaks minishell");
	}
	free_action_list(&start);
}


