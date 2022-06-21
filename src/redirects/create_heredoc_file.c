/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_heredoc_file.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 22:01:28 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/21 22:01:31 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_hex_value(unsigned long num)
{
	char	*str;
	int32_t	i;

	i = 11;
	str = ft_calloc(13, sizeof(char));
	if (!str)
		return (NULL);
	while (num > 0)
	{
		if (num % 16 < 10)
			str[i] = num % 16 + '0';
		else
			str[i] = num % 16 + 'a' - 10;
		num /= 16;
		i--;
	}
	return (str);
}

static void	set_heredoc_path_in_node(action_t *heredoc_node, char *path)
{
	free(heredoc_node->arg[0]);
	heredoc_node->arg[0] = path;
}

static int32_t	add_to_heredoc_paths(heredoc_t **filepaths, char *new_path)
{
	heredoc_t	*new;
	heredoc_t	*tmp;

	new = malloc(sizeof(heredoc_t) * 1);
	if (!new)
		return (-1);
	new->next = NULL;
	new->path = ft_strdup(new_path);
	if (!new->path)
	{
		free(new);
		return (-1);
	}
	tmp = *filepaths;
	if (!tmp)
	{
		*filepaths = new;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

int32_t	create_heredoc_file(action_t *heredoc_node, heredoc_t **file_paths)
{
	int32_t	fd;
	char	*pointer_address;
	char	*path;

	path = ft_calloc(33, sizeof(char));
	if (!path)
		return (-1);
	pointer_address = get_hex_value((unsigned long)heredoc_node->arg[0]);
	if (!pointer_address)
		return (-1);
	ft_bzero(path, 33);
	ft_strlcat(path, "/tmp/.tmp_heredoc0x", 33);
	ft_strlcat(path, pointer_address, 33);
	free(pointer_address);
	set_heredoc_path_in_node(heredoc_node, path);
	fd = open(path, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
		return (-1);
	close(fd);
	if (add_to_heredoc_paths(file_paths, path) == -1)
	{
		unlink(path);
		return (-1);
	}
	return (0);
}
