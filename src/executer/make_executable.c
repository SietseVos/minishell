#include "minishell.h"

void	free_pp(char **pp, int size)
{
	int	count;

	count = 0;
	while (size >= 0)
	{
		free(pp[size]);
		size--;
	}
	free(pp);
}

int	pplen(char **pp)
{
	int	i;

	i = 0;
	while (pp[i] != NULL)
		i++;
	return (i);
}

char	**get_bin_paths(char **envp)
{
	char	*binpaths;

	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	binpaths = *envp + 5;
	return (ft_split(binpaths, ':'));
}

char	*get_cmd_with_path(char *path, char *cmd)
{
	char	*ret;
	char	*fullpath;

	fullpath = ft_strjoin(path, "/");
	if (fullpath == NULL)
		nullerr("failed to join path with /");
	ret = ft_strjoin(fullpath, cmd);
	if (ret == NULL)
	{
		free(fullpath);
		nullerr("failed to join path with command");
	}
	free(fullpath);
	return (ret);
}

char	*get_executable(char *cmd, char **envp)
{
	char	**paths;
	char	*ret;
	int		i;

	i = 0;
	paths = get_bin_paths(envp);
	if (paths == NULL)
		nullerr("failed to get paths");
	while (paths[i] != NULL)
	{
		ret = get_cmd_with_path(paths[i], cmd);
		printf("binary: %s\n", ret);
		if (access(ret, F_OK) == 0)
		{
			free_pp(paths, pplen(paths));
			return (ret);
		}
		free(ret);
		i++;
	}
	free_pp(paths, pplen(paths));
	nullerr("binary is invalid");
	return (ret);
}
