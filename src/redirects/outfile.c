
#include "minishell.h"

static void	check_if_file_exists(char *path)
{
	int32_t	fd;

	fd = -1;
	if (access(path, F_OK) == -1)
		fd = open(path, O_CREAT);
	if (fd != -1)
		close(fd);
}

static int32_t	check_premissions(char *path)
{
	if (access(path, R_OK) == -1)
	{
		printf("bash: %s: Premission denied\n", path);
		return (false);
	}
	return (true);
}

int32_t	get_outfile_fd(action_t	*action)
{
	int32_t	fd;

	fd = -2;
	while (action && action->type != PIPE)
	{
		if (action->type == TRUNC || action->type == APPEND)
		{
			if (fd != -2)
				close(fd);
			check_if_file_exists(action->arg[0]);
			if (check_premissions(action->arg[0]) == false)
				return (-1);
			if (action->type == APPEND)
				fd = open(action->arg[0], O_WRONLY | O_APPEND);
			else
				fd = open(action->arg[0], O_WRONLY | O_TRUNC);
			if (fd == -1)
				return (-1);
		}
		action = action->next;
	}
	return (fd);
}
