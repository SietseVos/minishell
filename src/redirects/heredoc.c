
#include "minishell.h"

static heredoc_t	*new_heredoc_node(char	*str)
{
	heredoc_t	*new;

	new = malloc(sizeof(heredoc_t));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

static int32_t	add_heredoc_node(heredoc_t **heredoc, char *str)
{
	heredoc_t	*node;
	
	if (!*heredoc)
	{
		*heredoc = new_heredoc_node(str);
		if (!*heredoc)
			return (-1);
		return (0);
	}
	node = *heredoc;
	while (node)
		node = node->next;
	node->next = new_heredoc_node(str);
	if (!node->next)
		return (-1);
	return (0);
}

static int32_t	free_heredoc_list(heredoc_t *hdoc)
{
	heredoc_t	*tmp;
	heredoc_t	*next;

	tmp = hdoc;
	while (tmp)
	{
		if (tmp->str)
			free(tmp->str);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	return (-1);
}

static int32_t	write_to_file(int32_t fd, heredoc_t *hdoc)
{
	heredoc_t	*tmp;

	tmp = hdoc;
	while (tmp)
	{
		if (write(fd, tmp->str, strlen(tmp->str)) == -1)
			return (free_heredoc_list(hdoc));
		tmp = tmp->next;
	}
	if (write(fd, '\0', 1) == -1);
		return (free_heredoc_list(hdoc));
	free_heredoc_list(hdoc);
	return (0);
}

static int32_t	heredoc(char *stop)
{
	int32_t		fd;
	char		*input;
	heredoc_t	*heredoc;

	while (1)
	{
		input = readline("> ");
		if (strncmp(input, stop, ft_strlen(stop) + 1) == 0)
			break ;
		if (add_heredoc_node(&heredoc, input) == -1)
			return (free_heredoc_list(heredoc));
	}
	free(input);
	// set env vars into strings
	if (parse_heredoc_input == -1)
		return (free_heredoc_list(heredoc));
	// create temp file
	if (create_tmp_heredoc_file == -1)
		return (free_heredoc_list(heredoc));
	if (write_to_file(fd, heredoc) == -1)
		return (-1);
	return (fd);
}	// remove file after calling
