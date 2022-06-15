
#include "minishell.h"

static bool	contains_pipes(action_t *actions)
{
	int32_t	pipe_count;
	
	pipe_count = 0;
	while (actions)
	{
		if (actions->type == PIPE)
			return (true);
		actions = actions->next;
	}
	return (false);
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

void	reset_redirections(int32_t in_fd, int32_t out_fd)
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

int32_t	set_redirections(action_t *actions, int32_t *in_fd, int32_t *out_fd)
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

bool	actions_only_builtins(action_t *actions) 
{
	while (actions && actions->type != PIPE)
	{
		if (actions->type == TOSTDOUT
			&& !((ft_strncmp(actions->arg[0], "cd", 3) == 0)
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

void	set_actions_next_pipe(action_t **actions)
{
	action_t	*tmp;

	tmp = *actions;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
		tmp = tmp->next;
	*actions = tmp;
}

child_pids_t	*get_first_pid_node(void)
{
	static child_pids_t	first;

	return (&first);
}

child_pids_t	*get_last_pid_node(void)
{
	child_pids_t	*tmp;

	tmp = get_first_pid_node();
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int32_t	save_pid(pid_t new_pid)
{
	child_pids_t	*new;
	child_pids_t	*last;

	new = malloc(sizeof(child_pids_t));
	if (!new)
		return (-1);
	new->pid = new_pid;
	new->next = NULL;
	last = get_last_pid_node();
	last->next = new;
	return (0);
}

void	reset_pid(void)
{
	child_pids_t	*tmp;
	child_pids_t	*next;

	tmp = get_first_pid_node();
	if (!tmp->next)
		return ;
	tmp = tmp->next;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	tmp =  get_first_pid_node();
	tmp->next = NULL;
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
	fork_fd = -1;
	return_value = 0;
	if (set_redirections(actions, &in_fd, &out_fd) == -1)
		return (-1);
	if (actions_only_builtins(actions))
	{
		if (run_buildins(actions, list) == -1)
			return (-1);
	}
	else
	{
		while (actions && actions->type != TOSTDOUT)
			actions = actions->next;
		if (!actions)
			return (-1);
		fork_fd = fork();
		if (fork_fd == 0)
		{
			return_execute = find_command_and_execute(actions->arg, list);
			if (return_execute == -1)
				exit (-1);
			else if (return_execute == 0)
			{
				printf("bash: %s: command not found\n", actions->arg[0]);
				exit (1);
			}
			exit (g_exit_status);
		}
	}
	reset_redirections(in_fd, out_fd);
	if (fork_fd > -1)
		if (save_pid(fork_fd) == -1)
			return (-1);
	return (return_value);
}

int32_t	run_child(action_t *actions, env_vars_t *list, int32_t *fd, int32_t fd_in)
{
	int32_t	return_execute;
	int32_t infile_fd;
	int32_t outfile_fd;

	// fprintf(stderr, "pipecount inside child: %d\n", get_pipe_count(actions));
	dup2(fd_in, STDIN_FILENO);
	if (fd)
	{
		close(fd[PIPE_READ]);
		dup2(fd[PIPE_WRITE], STDOUT_FILENO);
		// fprintf(stderr, "child reading from %d and writing to %d\n", fd_in, fd[PIPE_WRITE]);
	}
	// else
	// 	fprintf(stderr, "child reading from %d and writing to %d\n", fd_in, STDOUT_FILENO);
	if (set_redirections(actions, &infile_fd, &outfile_fd) == -1)
		exit (-1);
	while (actions && actions->type != TOSTDOUT)
		actions = actions->next;
	// fprintf(stderr, "^ Function %s ^\n", actions->arg[0]);
	if (!actions)
		exit (-1);
	return_execute = find_command_and_execute(actions->arg, list);
	if (return_execute == -1)
		exit (-1);
	else if (return_execute == 0)
	{
		// fprintf(stderr, "bash: %s: command not found\n", actions->arg[0]);
		exit (1);
	}
	reset_redirections(infile_fd, outfile_fd);
	exit (g_exit_status);
}

int32_t	run_with_pipes(action_t *actions, env_vars_t *list, int32_t fd_in)
{
	const bool	pipes = contains_pipes(actions);
	int32_t		pipe_fds[2];
	pid_t		fork_pid;

	if (pipes == false)
	{
		fork_pid = fork();
		if (fork_pid == -1)
			return (-1);
		else if (fork_pid == 0)
			return (run_child(actions, list, NULL, fd_in));
		return (0);
	}
	if (pipe(pipe_fds) == -1)
		return (-1);
	// printf("pipe created! fds: %d - %d\n", pipe_fds[0], pipe_fds[1]);
	fork_pid = fork();
	if (fork_pid == -1)
		return (-1);
	else if (fork_pid == 0)
		run_child(actions, list, pipe_fds, fd_in);
	if (fd_in > 0)
		close(fd_in);
	close(pipe_fds[PIPE_WRITE]);
	if (save_pid(fork_pid) == -1)
		return (-1);
	set_actions_next_pipe(&actions);
	return (run_with_pipes(actions, list, pipe_fds[PIPE_READ]));
}

void	set_exit_status_and_wait(void)
{
	child_pids_t	*node;
	child_pids_t	*last_child;
	int32_t			return_wait;

	node = get_first_pid_node();
	last_child = get_last_pid_node();
	waitpid(last_child->pid, &return_wait, 0);
	while (node && node->next)
	{
		wait(NULL);
		node = node->next;
	}
	reset_pid();
	g_exit_status = WIFEXITED (return_wait);
}

int32_t	executer(action_t *actions, env_vars_t *list)
{
	int32_t	return_value;

	if (contains_pipes(actions))
	{
		// printf("Pipes detected!\n");
		return_value = run_with_pipes(actions, list, STDIN_FILENO);
		if (return_value == -1)
		{
			reset_pid();
			return (-1);
		}
		dup2(STDERR_FILENO, STDIN_FILENO);
		if (return_value == -1)
		{
			set_exit_status_and_wait();
			return (-1);
		}
		set_exit_status_and_wait();
		return (g_exit_status);
	}
	else
	{
		// printf("no pipes!\n");
		return_value = run_no_pipes(actions, list);
		set_exit_status_and_wait();
	}
	return (return_value);
}
