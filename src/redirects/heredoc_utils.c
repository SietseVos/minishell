/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 18:10:23 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 16:29:31 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int32_t	get_total_str_len(char *input, env_vars_t *env)
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

int32_t	expand_heredoc(char **input, int32_t type, env_vars_t *env)
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
