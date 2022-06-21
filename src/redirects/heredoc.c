
#include "minishell.h"

static int32_t	ft_strcmp(char *str1, char *str2)
{
	int32_t	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	if (str1[i] != str2[i])
		return (-1);
	return (0);
}

static int32_t	close_free_and_return(int32_t fd, char *str1, \
								char *str2, int32_t return_v)
{
	if (fd > 0)
		close(fd);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (return_v);
}

// ctrl c signal should work
static int32_t	run_heredoc(const char *heredoc_path, char *delimiter)
{
	int32_t	fd;
	char	*in;

	fd = open(heredoc_path, O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (-1);
	while (1)
	{
		in = readline("> ");
		if (!in)
			return (close_free_and_return(fd, delimiter, NULL, 0));
		else if (in[0] == '\0')
		{
			if (write(fd, "\n", 1) == -1)
				return (close_free_and_return(fd, delimiter, in, -1));
			continue ;
		}
		// expand variables
		if (ft_strcmp(delimiter, in) == 0)
			return (close_free_and_return(fd, delimiter, in, 0));
		else if (write(fd, in, ft_strlen(in)) == -1 || write(fd, "\n", 1) == -1)
			return (close_free_and_return(fd, delimiter, in, -1));
		free(in);
	}
	return (0);
}

void	remove_heredoc_files(heredoc_t **files)
{
	heredoc_t	*next;

	if (!files || !*files)
		return ;
	while (*files)
	{
		next = (*files)->next;
		if ((*files)->path)
		{
			unlink((*files)->path);
			free((*files)->path);
		}
		free(*files);
		*files = next;
	}
}

int32_t	heredoc(action_t *actions, heredoc_t **file_paths)
{
	char	*delimiter;

	while (actions)
	{
		if (actions->type == HDOC)
		{
			delimiter = ft_strdup(actions->arg[0]);
			if (!delimiter || create_heredoc_file(actions, file_paths) == -1)
				return (-1);
			if (run_heredoc(actions->arg[0], delimiter) == -1)
				return (-1);
		}
		actions = actions->next;
	}
	return (0);
}
