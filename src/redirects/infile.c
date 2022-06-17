
#include "minishell.h"

static bool	access_error(action_t *action)
{
	while (action && action->type != PIPE)
	{
		if (action->type == INFILE)
		{
			if (access(action->arg[0], F_OK) == -1)
			{
				g_exit_status = 1;
				printf("bash: %s: No such file or directory", action->arg[0]);
				return (true);
			}
			else if (access(action->arg[0], R_OK) == -1)
			{
				g_exit_status = 1;
				printf("bash: %s: Premission denied\n", action->arg[0]);
				return (true);
			}
		}
		action = action->next;
	}
	return (false);
}

int32_t	get_infile_fd(action_t	*action)
{
	int32_t	fd;

	fd = -2;
	if (access_error(action))
		return (-1);
	while (action && action->type != PIPE)
	{
		if (action->type == INFILE)
		{
			if (fd != -2)
				close(fd);
			fd = open(action->arg[0], O_RDONLY);
			if (fd == -1)
				return (-1);
		}
		action = action->next;
	}
	return (fd);
}
