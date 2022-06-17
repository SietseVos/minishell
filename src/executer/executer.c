
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

int32_t	run_no_pipes(action_t *actions, env_vars_t *list)
{
	int32_t	return_execute;
	int32_t	fork_fd;
	int32_t in_fd;
	int32_t out_fd;

	in_fd = -1;
	out_fd = -1;
	fork_fd = -1;
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
		if (fork_fd == -1)
			return (-1);
		if (fork_fd == 0)
		{
			return_execute = execute_command(actions->arg, list);
			if (return_execute == -1)
				exit (-1);
			else if (return_execute == 0)
			{
				printf("bash: %s: command not found\n", actions->arg[0]);
				exit (1);
			}
			exit (g_exit_status);
		}
		save_pid(fork_fd);
	}
	reset_redirections(in_fd, out_fd);
	if (fork_fd > -1)
		if (save_pid(fork_fd) == -1)
			return (-1);
	return (0);
}

int32_t	run_child(action_t *actions, env_vars_t *list, int32_t *fd, int32_t fd_in)
{
	int32_t	return_execute;
	int32_t infile_fd;
	int32_t outfile_fd;

	dup2(fd_in, STDIN_FILENO);
	if (fd)
	{
		close(fd[PIPE_READ]);
		dup2(fd[PIPE_WRITE], STDOUT_FILENO);
	}
	if (set_redirections(actions, &infile_fd, &outfile_fd) == -1)
		exit (-1);
	while (actions && actions->type != TOSTDOUT)
		actions = actions->next;
	if (!actions)
		exit (-1);
	return_execute = execute_command(actions->arg, list);
	if (return_execute == -1)
		exit (-1);
	else if (return_execute == 0)
		exit (1);
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
		if (fd_in > 0)
			close(fd_in);
		return (0);
	}
	if (pipe(pipe_fds) == -1)
		return (-1);
	fork_pid = fork();
	if (fork_pid == -1) // close pipe
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

int32_t	executer(action_t *actions, env_vars_t *list)
{
	int32_t		return_value;
	action_t	*copy;

	copy = actions;
	if (contains_pipes(copy))
	{
		return_value = run_with_pipes(copy, list, STDIN_FILENO);
		dup2(STDERR_FILENO, STDIN_FILENO);
	}
	else
		return_value = run_no_pipes(copy, list);
	set_exit_status_and_wait();
	reset_pid();
	free_action_list(actions);
	return (return_value);
}
