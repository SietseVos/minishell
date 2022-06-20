
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

static int32_t	close_free_and_return(int32_t fd, char *str1, char *str2, int32_t return_v)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (return_v);
}

static int32_t	run_heredoc(const char *heredoc_path, char *delimiter)
{
	int32_t	fd;
	char	*input;

	// ctrl c signal should work
	fd = open(heredoc_path, O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (!input)
			return(close_free_and_return(fd, delimiter, NULL, 0));
		// expand variables
		if (input[0] == '\0' || ft_strcmp(delimiter, input) == 0)
			return (close_free_and_return(fd, delimiter, input, 0));
		else if (write(fd, input, ft_strlen(input)) == -1 || write(fd, "\n", 1) == -1)
			return (close_free_and_return(fd, delimiter, input, -1));
		free(input);
	}
	close(fd);
	return (0);
}

void	remove_heredoc_files(action_t *actions)
{
	while (actions)
	{
		if (actions->type == HDOC)
			unlink(actions->arg[0]);
		actions = actions->next;
	}
}

int32_t	heredoc(action_t *actions)
{
	char	*delimiter;

	while (actions)
	{
		if (actions->type == HDOC)
		{
			delimiter = ft_strdup(actions->arg[0]);
			if (!delimiter || create_heredoc_file(actions) == -1)
				return (-1);
			if (run_heredoc(actions->arg[0], delimiter) == -1)
				return (-1);
		}
		actions = actions->next;
	}
	return (0);
}
