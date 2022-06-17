
#include "minishell.h"

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
