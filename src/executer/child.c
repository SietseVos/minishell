
#include "minishell.h"

static void	exit_and_close_fds(int32_t infile_fd, int32_t outfile_fd, int32_t fd_in)
{
	close(fd_in);
	reset_redirections(infile_fd, outfile_fd);
	exit (g_exit_status);
}

void	run_child(info_t *info, int32_t *fd, int32_t fd_in, bool contains_pipes)
{
	int32_t infile_fd;
	int32_t outfile_fd;

	dup2(fd_in, STDIN_FILENO);
	if (contains_pipes)
	{
		close(fd[PIPE_READ]);
		dup2(fd[PIPE_WRITE], STDOUT_FILENO);
	}
	if (set_redirections(info->action, &infile_fd, &outfile_fd) == -1)
		exit (1);
	pop_nodes_till_command(info->action);
	if (!info->action)
		exit_and_close_fds(infile_fd, outfile_fd, fd_in);
	else if (run_if_builtin_child(info))
		exit_and_close_fds(infile_fd, outfile_fd, fd_in);
	execute_command(info->action->arg, info->list);
	exit_and_close_fds(infile_fd, outfile_fd, fd_in);
}
