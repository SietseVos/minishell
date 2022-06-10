
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

int32_t	run_no_pipes(action_t *actions, env_vars_t *list)
{
	int32_t	return_value;
	int32_t	infile_fd;
	int32_t	outfile_fd;

	infile_fd = get_infile_fd(actions);
	if (infile_fd == -1)
		return (-1);
	outfile_fd = get_outfile_fd(actions);
	if (outfile_fd == -1)
	{
		close(infile_fd);
		return (-1);
	}
}

int32_t	executer(action_t *actions, env_vars_t *list)
{
	int32_t	pipe_count;
	int32_t	return_value;

	pipe_count = get_pipe_count(actions);
	if (pipe_count)
		// return_value = run with forks
	else
		// return_value = run without forking
	return (return_value);
}



/// 