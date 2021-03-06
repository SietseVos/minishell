/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_to_lst.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:05:47 by svos          #+#    #+#                 */
/*   Updated: 2022/07/04 14:12:57 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief copy until a single of double quote is found
 * 
 * @param dst - destination string (User has to make sure that
 * 				there's enough memory allocoted)
 * @param src - source string
 * @param i - pointer to source iterater
 * @param envp - environment variables
 * @return int32_t - stringlength of the copied string
 */
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

/**
 * @brief - copy until a whitespace is found
 * 
 * @param dst - destination string (User has to make sure that
 * 				there's enough memory allocoted)
 * @param src - source string
 * @param i - pointer to source iterater
 * @param envp - environment variables
 * @return int32_t - stringlength of the copied string
 */
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

/**
 * @brief - place a sting in a node
 * 
 * @param dst - destination string (User has to make sure
 * 				that there's enough memory allocoted)
 * @param src - source string
 * @param i - pointer to source iterater
 * @param envp - environment variables
 * @return * void 
 */
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
