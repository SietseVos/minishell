/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 15:51:59 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 17:50:27 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Fucntion to run an executable without a pipe before or after it.
 * 
 * @param actions Pointer to the head of the action list.
 * 
 * @param list Pointer to the environment variable list.
 * 
 * @return - [0] executed normally - [-1] fork failed
 * - [1] no more actions left -
*/
static int32_t	run_executable_no_pipe(t_action	**actions, t_env_vars *list)
{
	int32_t	return_execute;
	int32_t	fork_fd;

	signal(SIGINT, sig_c_outside_fork);
	while ((*actions) && (*actions)->type != TOSTDOUT)
		pop_action_node(actions);
	if (!actions)
		return (1);
	fork_fd = fork();
	if (fork_fd == -1)
		return (-1);
	if (fork_fd == 0)
	{
		signal(SIGINT, SIG_DFL);
		return_execute = execute_command((*actions)->arg, list);
		if (return_execute == -1)
			exit (1);
		else if (return_execute == 0)
			exit_with_error_message("minishell: ", (*actions)->arg[0], \
									": command not found\n", 1);
		exit (g_info.exit_status);
	}
	save_pid(fork_fd);
	return (0);
}

/**
 * Fucntion to run a builtin or executable without pipes.
 * 
 * @param actions Pointer to the head of the action list.
 * 
 * @param list Pointer to the environment variable list.
 * 
 * @return - [0] executed normally - [-1] redirection failed / builtin failed /
 * executable failed -
*/
static int32_t	run_no_pipes(t_action **actions, t_env_vars **list)
{
	int32_t	in_fd;
	int32_t	out_fd;

	in_fd = -1;
	out_fd = -1;
	if (set_redirections(*actions, &in_fd, &out_fd) == -1)
		return (-1);
	if (actions_only_builtins(*actions))
	{
		if (run_builtin_no_pipe(actions, list) == -1)
			return (-1);
	}
	else if (run_executable_no_pipe(actions, *list) == -1)
		return (-1);
	reset_redirections(in_fd, out_fd);
	return (0);
}

/**
 * Function that can be used to close the given pipe and file descriptor.
 * 
 * @param pipe_fds Pointer to the array cointaining fds from a single pipe.
 * 
 * @param fd_in Integer containing the file descriptor used as infile.
 * 
 * @return - [-1] -
*/
static int32_t	close_fds_and_return(int32_t *pipe_fds, int32_t fd_in)
{
	if (close(pipe_fds[0]) == -1)
		exit_with_error_message("close failed\n", NULL, NULL, 1);
	if (close(pipe_fds[1]) == -1)
		exit_with_error_message("close failed\n", NULL, NULL, 1);
	if (close(fd_in) == -1)
		exit_with_error_message("close failed\n", NULL, NULL, 1);
	return (-1);
}

/**
 * Function to run all actions within pipes.
 * Uses recursion to execute all actions behind each other
 * without waiting for one to finish.
 * 
 * @param info Struct containing pointers to both the head of the action
 * struct and the environment variable struct.
 * 
 * @param fd_in file descriptor pointing towards the input of the executable.
 * 
 * @return - [0] everything executed properly - [-1] close failed
 * / fork failed / pipe failed -
*/
static int32_t	run_with_pipes(t_info info, int32_t fd_in)
{
	const bool	has_pipes = contains_pipes((*info.action));
	int32_t		pipe_fds[2];
	pid_t		fork_pid;

	signal(SIGINT, sig_c_outside_fork);
	if (has_pipes && pipe(pipe_fds) == -1)
		return (close_fd_return_error(PIPE_ERROR, fd_in, -1));
	fork_pid = fork();
	if (has_pipes && fork_pid == -1) // should be ony fork == -1??
	{
		write(STDERR_FILENO, FORK_ERROR, 51);
		return (close_fds_and_return(pipe_fds, fd_in));
	}
	else if (fork_pid == 0)
		run_child(info, pipe_fds, fd_in, has_pipes);
	if (fd_in > 0)
	{
		if (close(fd_in) == -1)
			exit_with_error_message("close failed\n", NULL, NULL, 1);
	}
	if (close(pipe_fds[PIPE_WRITE]) == -1)
		exit_with_error_message("close failed\n", NULL, NULL, 1);
	if (save_pid(fork_pid) == -1)
		return (-1);
	set_actions_next_pipe(info.action);
	if (has_pipes == false)
		return (0);
	return (run_with_pipes(info, pipe_fds[PIPE_READ]));
}

/**
 * Function used to execute all action nodes that contain a builtin or
 * executable.
 * 
 * @param actions Pointer to the head of the action list.
 * 
 * @param list Pointer to the head of the environment variable list.
 * 
 * @return - [0] everything eecuted properly - 
 * [-1] error occurred whilst trying to execute -
*/
int32_t	executer(t_action **actions, t_env_vars **list)
{
	int32_t		return_value;
	t_info		info;

	info.action = actions;
	info.list = list;
	signal(SIGINT, handle_sig_executer);
	signal(SIGQUIT, handle_sig_executer);
	if (contains_pipes((*info.action)))
	{
		return_value = run_with_pipes(info, STDIN_FILENO);
		if (dup2(STDERR_FILENO, STDIN_FILENO) == -1)
			exit_with_error_message("dup2 failed\n", NULL, NULL, 1);
	}
	else
		return_value = run_no_pipes(actions, list);
	set_exit_status_and_wait();
	reset_pid();
	free_action_list(actions);
	return (return_value);
}
