/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_to_lst.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:05:47 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:50:04 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int32_t	copy_til_quote(char *dst, char *src,
					int32_t *i, t_env_vars *envp)
{
	char	c;
	int32_t	j;

	c = src[*i];
	*i += 1;
	j = 0;
	while (src[*i] != '\0' && src[*i] != c)
	{
		if (src[*i] == '$' && c == '"')
			*i += place_envvar_quote(dst + j, src + *i, envp, &j);
		else
		{
			dst[j] = src[*i];
			*i += 1;
			j++;
		}
	}
	if (src[*i] == c)
		*i += 1;
	return (j);
}

static int32_t	copy_til_space(char *dst, char *src,
					int32_t *i, t_env_vars *envp)
{
	int32_t	j;

	j = 0;
	while (src[*i] != '\0' && is_whitespace(src[*i]) == false
		&& src[*i] != '"' && src[*i] != '\'')
	{
		if (src[*i] == '$')
			*i += place_envvar_space(dst + j, src + *i, envp, &j);
		else
		{
			dst[j] = src[*i];
			*i += 1;
			j++;
		}
	}
	return (j);
}

void	place_str_in_node(char *dst, char *src, int32_t *i, t_env_vars *envp)
{
	int	j;

	j = 0;
	while (src[*i] != '\0' && is_whitespace(src[*i]) == false)
	{
		if (src[*i] == '"' || src[*i] == '\'')
			j += copy_til_quote(dst + j, src, i, envp);
		else
			j += copy_til_space(dst + j, src, i, envp);
	}
	dst[j] = '\0';
	while (is_whitespace(src[*i]) == true)
		*i += 1;
}
