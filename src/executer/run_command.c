#include "minishell.h"
#include <sys/wait.h>

static bool	run_command(action_t *acts, char **envp)
{
	printf("executing a command\n");
	execve(acts->arg[0], acts->arg, envp);
	(void)acts;
	(void)envp;
	return (true);
}

void	pipe_to_file(char **cmd, int32_t fdread, int32_t fdwrite, char **envp)
{
	int32_t	pid;
	int32_t	status;

	pid = fork();
	if (pid == -1)
		boolerr("failed to fork");
	if (pid == 0)
	{
		printf("dupping fd %d to stdout.\n", fdwrite);
		dup2(fdwrite, 1);
		dup2(fdread, 0);
		execve(cmd[0], cmd, envp);
	}
	waitpid(pid, &status, 0);
}

bool	pipe_command(action_t *acts, int32_t fdread, char **envp)
{
	int32_t	fd[2];
	int32_t	pid;
	// int32_t	status;

	if (pipe(fd) == -1)
		return (boolerr("failed to pipe"));
	pid = fork();
	if (pid == -1)
		boolerr("failed to fork");
	if (pid == 0)
	{
		printf("entered child\n");
		close(fd[0]);
		dup2(fd[1], 1);
		dup2(fdread, 0);
		run_command(acts, envp);
		nullerr("skipped execve");
	}
	else
	{
		close(fd[1]);
		if (fdread != 0)
			close(fdread);
		// waitpid(pid, &status, 0);
		printf("entered parent\n");
		return (fd[0]);
	}
	exit(0);
}
