
#include "minishell.h"

static int32_t	run_executable_no_pipe(action_t	*actions, env_vars_t *list)
{
	int32_t	return_execute;
	int32_t	fork_fd;

	while (actions && actions->type != TOSTDOUT)
		pop_action_node(&actions);
	if (!actions)
		return (1);
	fork_fd = fork();
	if (fork_fd == -1)
		return (-1);
	if (fork_fd == 0)
	{
		return_execute = execute_command(actions->arg, list);
		if (return_execute == -1)
			exit (1);
		else if (return_execute == 0)
		{
			printf("bash: %s: command not found\n", actions->arg[0]);
			exit (1);
		}
		exit (g_exit_status);
	}
	save_pid(fork_fd);
	return (0);
}

int32_t	run_no_pipes(action_t *actions, env_vars_t *list)
{
	int32_t	in_fd;
	int32_t	out_fd;

	in_fd = -1;
	out_fd = -1;
	if (set_redirections(actions, &in_fd, &out_fd) == -1)
		return (-1);
	if (actions_only_builtins(actions))
	{
		if (run_builtin_no_pipe(actions, list) == -1)
			return (-1);
	}
	else if (run_executable_no_pipe(actions, list) == -1)
		return (-1);
	reset_redirections(in_fd, out_fd);
	return (0);
}

static int32_t	close_fds_and_return(int32_t *pipe_fds, int32_t fd_in)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	close(fd_in);
	return (-1);
}

static int32_t	run_with_pipes(info_t *info, int32_t fd_in)
{
	const bool	has_pipes = contains_pipes(info->action);
	int32_t		pipe_fds[2];
	pid_t		fork_pid;

	if (has_pipes && pipe(pipe_fds) == -1)
		return (-1);
	fork_pid = fork();
	if (has_pipes && fork_pid == -1)
		close_fds_and_return(pipe_fds, fd_in);
	else if (fork_pid == 0)
		run_child(info, pipe_fds, fd_in, has_pipes);
	if (fd_in > 0)
		close(fd_in);
	close(pipe_fds[PIPE_WRITE]);
	if (save_pid(fork_pid) == -1)
		return (-1);
	set_actions_next_pipe(&info->action);
	if (has_pipes == false)
		return (0);
	return (run_with_pipes(info, pipe_fds[PIPE_READ]));
}

int32_t	executer(action_t *actions, env_vars_t *list)
{
	int32_t		return_value;
	info_t		info;

	info.action = actions;
	info.list = list;
	if (contains_pipes(info.action))
	{
		return_value = run_with_pipes(&info, STDIN_FILENO);
		dup2(STDERR_FILENO, STDIN_FILENO);
	}
	else
		return_value = run_no_pipes(info.action, list);
	set_exit_status_and_wait();
	reset_pid();
	free_action_list(actions);
	return (return_value);
}
