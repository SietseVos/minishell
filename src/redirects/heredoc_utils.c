/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 18:10:23 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/05 14:08:04 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to get the total string length of the string
 * after environment variable expansion.
 * 
 * @param input Pointer to the string that has environment variable(s).
 * 
 * @param env Pointer to the environment variable list.
 * 
 * @return - [len] length of the total string after expansion -
*/
static int32_t	get_total_str_len(char *input, t_env_vars *env)
{
	int32_t	len;
	int32_t	i;

	i = 0;
	len = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] != ' ')
		{
			i += interpvar_strlen(&input[i], '\0', &len, env);
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

/**
 * Function to expand the input line of the heredoc
 * with the environment variables.
 * 
 * @param input Double char pointer to the pointer containing the
 * input from the heredoc.
 * 
 * @param type The type of heredoc 
 * (if it has quotes/should be expanded or not).
 * 
 * @param env Pointer to the environment variable list.
 * 
 * @return - [0] success - [-1] mallloc failed -
*/
int32_t	expand_heredoc(char **input, int32_t type, t_env_vars *env)
{
	char	*new_str;
	int32_t	i;
	int32_t	j;

	i = 0;
	j = 0;
	if (type == HDOCQUOTE)
		return (0);
	new_str = ft_calloc(get_total_str_len((*input), env) + 1, sizeof(char));
	if (!new_str)
		return (-1);
	while ((*input)[i])
	{
		if ((*input)[i] == '$' && (*input)[i + 1] != ' ')
		{
			i += place_envvar_space(&new_str[j], &(*input)[i], env, &j);
			continue ;
		}
		new_str[j] = (*input)[i];
		i++;
		j++;
	}
	free(*input);
	*input = new_str;
	return (0);
}

/**
 * Lazy strncmp without the need to specify the size to compare.
 * 
 * @param str1 The first string to compare.
 * 
 * @param str2 The second string to compare against the first.
 * 
 * @return - [0] strings are equal - [-1] strings differ -
*/
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

/**
 * This function will get the input from terminal
 * and write it into a file.
 * 
 * @param heredoc_path The path towards the heredoc file.
 *
 * @param delimiter Pointer to the string containing the heredoc delimiter.
 * 
 * @param type The type of heredoc (with or without expansion).
 * 
 * @param env Pointer to the environment variable list.
 * 
 * @return - [0] success - [-1] signal interupted / heredoc failed - 
*/
void	read_input_and_write_to_heredoc(const char *heredoc_path, \
						char *delimiter, int32_t type, t_env_vars *env)
{
	int32_t	fd;
	char	*in;

	in = NULL;
	fd = open(heredoc_path, O_WRONLY | O_TRUNC);
	if (fd == -1)
		exit (-1);
	while (1)
	{
		in = readline("> ");
		if (!in)
			exit (close_free_and_return(fd, delimiter, NULL, 0));
		if (ft_strcmp(delimiter, in) == 0)
			exit (close_free_and_return(fd, delimiter, in, 0));
		if (expand_heredoc(&in, type, env) == -1)
			exit (close_free_and_return(fd, delimiter, in, -1));
		else if (write(fd, in, ft_strlen(in)) == -1 || write(fd, "\n", 1) == -1)
			exit (close_free_and_return(fd, delimiter, in, -1));
		free(in);
	}
}
