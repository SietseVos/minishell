#include "minishell.h"

int32_t	set_fds(int32_t *fdin, int32_t *fdout, action_t *actions)
{
	if (actions ->type == INFILE)
		*fdin = open(actions ->arg[0], O_RDONLY);
	else if (actions ->type == OUTFILE)
		*fdout = open(actions ->arg[0], O_TRUNC | O_CREAT);
	else if (actions ->type == APPEND)
		*fdout = open(actions ->arg[0], O_APPEND | O_CREAT);
	if (*fdin == -1 || *fdout == -1)
		return (-1);
	actions = actions ->next;
}

int32_t	action_loop(action_t *actions, env_vars_t *envp)
{
	int32_t	fdin;
	int32_t	fdout;
	while (actions)
	{
		if (actions ->type == INFILE || actions ->type == TRUNC || actions ->type == APPEND)
			if (set_fds(&fdin, &fdout, actions) == -1)
				return (-1);

	}
}

int	pipe_to_cmd(int fd_in, char **cmd, char **envp)
{
	int	fd[2];
	int	pid;
	int	status;

	pipe(fd);
	pid = fork();
	if (pid == -1)
		error_msg("fork");
	if (pid != 0)
	{
		close(fd[1]);
		close(fd_in);
		printf("entered parent\n");
		return (fd[0]);
	}
	else
	{
		printf("entered child\n");
		close(fd[0]);
		dup2(fd[1], 1);
		dup2(fd_in, 0);
		execve(cmd[0], cmd, envp);
		error_msg("skipping execve in pipe to cmd");
	}
	return (0);
}
