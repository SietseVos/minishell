/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 18:10:23 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 21:31:12 by rvan-mee      ########   odam.nl         */
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
