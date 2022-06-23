/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_to_lst.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:05:47 by svos          #+#    #+#                 */
/*   Updated: 2022/06/23 18:21:08 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interp_exit_status(char *dst, int32_t *i)
{
	int32_t	j;
	int32_t	cpy;

	j = 0;
	cpy = g_exit_status;
	if (cpy == 0)
	{
		dst[j] = '0';
		*i += 1;
		return ;
	}
	while (cpy > 0)
	{
		cpy = cpy / 10;
		j++;
	}
	cpy = g_exit_status;
	j--;
	while (cpy > 0)
	{
		dst[j] = cpy % 10 + '0';
		cpy = cpy / 10;
		j--;
		*i += 1;
	}
}

int32_t	place_envvar(char *dst, char *src, env_vars_t *envp, int32_t *i)
{
	int32_t	varlen;

	varlen = envvarlen(src, '"');
	if (varlen == 2 && src[1] == '?')
	{
		interp_exit_status(dst, i);
		return (varlen);
	}
	// if (varlen == 1)
	// {
	// 	if (c == ' ' && is_whitespace(str[1]))
	// 		*strlen += 1;
	// 	else if (c == '"' || c == '\'')
	// 		*strlen += 1;
	// 	return (varlen);
	// }
	while (envp)
	{
		if (ft_strncmp(envp ->str, src + 1, varlen - 1) == 0
			&& envp ->str[varlen - 1] == '=')
		{
			ft_strlcpy(dst, envp ->str + varlen,
				ft_strlen(envp ->str + varlen) + 1);
			*i += ft_strlen(envp ->str + varlen);
			return (varlen);
		}
		envp = envp ->next;
	}
	return (varlen);
}

int32_t	copy_til_quote(char *dst, char *src, int32_t *i, env_vars_t *envp)
{
	char	c;
	int32_t	j;

	c = src[*i];
	*i += 1;
	j = 0;
	while (src[*i] != '\0' && src[*i] != c)
	{
		if (src[*i] == '$' && c == '"')
			*i += place_envvar(dst + j, src + *i, envp, &j);
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

int32_t	copy_til_space(char *dst, char *src, int32_t *i, env_vars_t *envp)
{
	int32_t	j;

	j = 0;
	while (src[*i] != '\0' && is_whitespace(src[*i]) == false
		&& src[*i] != '"' && src[*i] != '\'')
	{
		if (src[*i] == '$')
			*i += place_envvar(dst + j, src + *i, envp, &j);
		else
		{
			dst[j] = src[*i];
			*i += 1;
			j++;
		}
	}
	return (j);
}

void	place_str_in_node(char *dst, char *src, int32_t *i, env_vars_t *envp)
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
