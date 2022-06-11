
#include "minishell.h"

static int32_t	get_pipe_count(action_t *actions)
{
	int32_t	pipe_count;

	pipe_count = 0;
	while (actions)
	{
		if (actions->type == PIPE)
			pipe_count++;
		actions = actions->next;
	}
	return (pipe_count);
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

static int32_t	dup_correct_fd(int32_t (file_function)(action_t *), action_t *actions, int32_t direction)
{
	int32_t	fd;

	fd = file_function(actions);
	if (fd == -2)
		return (-2);
	else if (fd == -1)	// if open fails or no premissions
		return (-1);
	close(direction);
	dup2(fd, direction);
	return (fd);
}

void	reset_in_out(int32_t in_fd, int32_t out_fd)
{
	if (in_fd > 0)
	{
		close(in_fd);
		close(STDIN_FILENO);
		dup2(STDERR_FILENO, STDIN_FILENO);
	}
	if (out_fd > 0)
	{
		close(out_fd);
		close(STDOUT_FILENO);
		dup2(STDERR_FILENO, STDOUT_FILENO);
	}
}

int32_t	set_in_out(action_t *actions, int32_t *in_fd, int32_t *out_fd)
{
	*in_fd = dup_correct_fd(get_infile_fd, actions, STDIN_FILENO);
	if (*in_fd == -1)
		return (-1);
	*out_fd = dup_correct_fd(get_outfile_fd, actions, STDOUT_FILENO);
	if (*out_fd == -1)
	{
		if (*in_fd > 0)
		{
			close(*in_fd);
			dup2(STDERR_FILENO, STDIN_FILENO);
		}
		return (-1);
	}
	return (0);
}

bool	actions_only_builtins(action_t *actions) // check ytpe 
{
	while (actions && actions->type != PIPE)
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

int32_t	run_buildins(action_t *actions, env_vars_t *list)
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
			exit_shell(&actions->arg[1], true);
		}
		else if (ft_strncmp(actions->arg[0], "export", 7) == 0)
			return_value_b = export(&actions->arg[1], list);
		else if (ft_strncmp(actions->arg[0], "pwd", 4) == 0)
			pwd();
		else if (ft_strncmp(actions->arg[0], "unset", 6) == 0)
			unset(&actions->arg[1], &list);
		if (return_value_i == -1 || return_value_b == false)
			return (-1);
		actions = actions->next;
	}
	return (0);
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

void	handle_sig_child(int32_t sig)
{
	(void)sig;
	printf("hey im here!\n");
}

int32_t	run_no_pipes(action_t *actions, env_vars_t *list)
{
	int32_t	return_value;
	int32_t	return_execute;
	int32_t	fork_fd;
	int32_t in_fd;
	int32_t out_fd;

	in_fd = -1;
	out_fd = -1;
	return_value = 0;
	if (actions_only_builtins(actions))
	{
		if (set_in_out(actions, &in_fd, &out_fd) == -1)
			return (-1);
		if (run_buildins(actions, list) == -1)
			return (-1);
	}
	else
	{
		while (actions && actions->type != TOSTDOUT)
			actions = actions->next;
		if (!actions)
			return (-1);
		if (set_in_out(actions, &in_fd, &out_fd) == -1)
			return (-1);
		fork_fd = fork();
		if (fork_fd == 0)
		{
			return_execute = find_command_and_execute(actions->arg, list);
			if (return_execute == -1)
				return (-1);
			else if (return_execute == 0)
			{
				printf("bash: %s: command not found\n", actions->arg[0]);
				return (1);
			}
			return (g_exit_status);
		}
		waitpid(fork_fd, &return_value, 0);
	}
	reset_in_out(in_fd, out_fd);
	return (return_value);
}

int32_t	executer(action_t *actions, env_vars_t *list)
{
	int32_t	pipe_count;
	int32_t	return_value;

	return_value = 0;
	pipe_count = get_pipe_count(actions);
	if (pipe_count)
		printf("Pipes detected! currently not supported\n");// return_value = run with forks
	else
		return_value = run_no_pipes(actions, list);
	return (return_value);
}
