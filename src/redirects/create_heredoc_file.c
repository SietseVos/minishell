/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_heredoc_file.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 22:01:28 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/08 15:31:43 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This unction converts the given unsigned long into hexadecimal
 * placed into a string.
 * 
 * @param num The number to be converted into hexadecimal.
 * 
 * @return - [str] a string contaning the number converted to hexadecimal -
 * [NULL] malloc failed -
*/
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

/**
 * This function creates and sets path towards the temporary heredoc file
 * into the heredoc node.
 * 
 * @param heredoc_node Pointer to the action node recieving the filepath.
 * 
 * @return - [0] path set successfully - [-1] malloc failed -
*/
static int32_t	set_heredoc_path_in_node(t_action *heredoc_node)
{
	char	*path;
	char	*pointer_address;

	path = ft_calloc(39, sizeof(char));
	if (!path)
		return (-1);
	pointer_address = get_hex_value((unsigned long)heredoc_node->arg[0]);
	if (!pointer_address)
	{
		free(path);
		return (-1);
	}
	ft_strlcat(path, "/tmp/.minishell_heredoc0x", 39);
	ft_strlcat(path, pointer_address, 39);
	free(pointer_address);
	free(heredoc_node->arg[0]);
	heredoc_node->arg[0] = path;
	return (0);
}

/**
 * This function adds to the heredoc linked list a new node containing the
 * given path.
 * 
 * @param filepaths Pointer to the head of the heredoc list.
 * 
 * @param new_path Pointer to the string containing the new path.
 * 
 * @return - [0] success - [-1] malloc failed - 
*/
static int32_t	add_to_heredoc_paths(t_heredoc **filepaths, char *new_path)
{
	t_heredoc	*new;
	t_heredoc	*tmp;

	new = malloc(sizeof(t_heredoc) * 1);
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

/**
 * Function to create a heredoc file and add the path to
 * the heredoc linked list. The name of the file will be
 * ".minishell_heredoc" with the pointer value of the delimiter
 * added behind it.
 * 
 * @param heredoc_node Pointer to the action node containing the delimiter
 * of the heredoc.
 * 
 * @param file_paths Pointer too the head of the heredoc linked list
 * contaning the paths to all fliles.
 * 
 * @return - [0] success - [-1] malloc failed -
*/
int32_t	create_heredoc_file(t_action *heredoc_node, t_heredoc **file_paths)
{
	int32_t	fd;

	if (set_heredoc_path_in_node(heredoc_node) == -1)
		return (-1);
	fd = open(heredoc_node->arg[0], O_RDWR | O_CREAT | O_TRUNC , 0666);
	if (fd == -1)
		return (-1);
	if (close(fd) == -1)
		exit_with_error_message("close failed\n", NULL, NULL, 1);
	if (add_to_heredoc_paths(file_paths, heredoc_node->arg[0]) == -1)
	{
		unlink(heredoc_node->arg[0]);
		return (-1);
	}
	return (0);
}
