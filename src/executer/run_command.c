#include "minishell.h"

// char	**get_paths(char **envp)
// {
// 	char	*bindirs;

// 	while (ft_strncmp(*envp, "PATH=", 5) != 0)
// 		envp++;
// 	bindirs = *envp + 5;
// 	return (ft_split(bindirs, ':'));
// }

// char	*get_cmd_with_path(char *path, char *cmd)
// {
// 	char	*ret;
// 	char	*pathdup;

// 	pathdup = ft_strdup(path);
// 	pathdup = ft_strjoin(pathdup, "/");
// 	if (pathdup == NULL)
// 		nullerr("ft_strjoin for pathdup");
// 	ret = ft_strjoin(pathdup, cmd);
// 	if (ret == NULL)
// 		nullerr("failed to join path with command");
// 	return (ret);
// }

// char	*get_executable(char *cmd, char **envp)
// {
// 	char	**paths;
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	paths = get_paths(envp);
// 	if (paths == NULL)
// 		nullerr("failed to get paths");
// 	while (paths[i] != NULL)
// 	{
// 		ret = get_cmd_with_path(paths[i], cmd);
// 		printf("binary: %s\n", ret);
// 		if (access(ret, F_OK) == 0)
// 		{
// 			free_pp(paths, pplen(paths));
// 			return (ret);
// 		}
// 		free(ret);
// 		i++;
// 	}
// 	free_pp(paths, pplen(paths));
// 	nullerr("binary is invalid");
// 	return (ret);
// }

static bool	run_command(action_t *acts, char **envp)
{
	printf("executing a command\n");
	(void)acts;
	(void)envp;
	return (true);
}

bool	pipe_command(action_t *acts, int32_t fdread, int32_t fdwrite, env_vars_t *envp)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (boolerr("failed to pipe"));
	pid = fork();
	if (pid == -1)
		boolerr("failed to fork");
	if (pid != 0)
	{
		close(fd[1]);
		if (fdread != 0)
			close(fdread);
		printf("entered parent\n");
		return (fd[0]);
	}
	else
	{
		printf("entered child\n");
		close(fd[0]);
		dup2(fd[1], 1);
		dup2(fdread, 0);
		run_command(acts, env_list_to_array(envp));
		nullerr("skipped execve");
	}
	(void)fdwrite;
	exit(0);
}
