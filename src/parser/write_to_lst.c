/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_to_lst.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:05:47 by svos          #+#    #+#                 */
/*   Updated: 2022/05/30 16:54:22 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	place_envvar(char *dst, char *src, env_vars_t *envp, int32_t *i)
{
	int32_t	varlen;

	varlen = envvarlen(src, '"');
	printf("varlen in place_envvar: %d\n", varlen);
	while (envp)
	{
		if (ft_strncmp(envp ->str, src + 1, varlen - 1) == 0 && envp ->str[varlen - 1] == '=')
		{
			printf("found environment variable in place_envvar: %s\n", envp ->str + varlen - 1);
			ft_strlcpy(dst, envp ->str + varlen, strlen_quote(envp ->str + varlen) + 1);
			// printf("i before variable increment: %d\n", *i);
			*i += strlen_quote(envp ->str + varlen);
			// printf("i after variable increment: %d\n", *i);
			return (varlen);
		}
		envp = envp ->next;
	}
	return (varlen);
}

void	strcpy_interpvar(char *dst, char *src, int32_t strlen, env_vars_t *envp)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	j = 0;
	printf("strlen in strcpy_interpvar function: %d\n", strlen);
	while (src[j] != '\0' && strlen > i + 1)
	{
		if (src[j] == '$')
		{
			dst[i] = src[j];
			j += place_envvar(dst + i, src + j, envp, &i);
		}
		else
		{
			printf("%c\n", src[j]);
			dst[i] = src[j];
			i++;
			j++;
		}
	}
	dst[i] = '\0';
}

int32_t	place_str_in_node(char *dst, char *src, int32_t strlen, env_vars_t *envp)
{
	printf("input to be put into destination: %s\n", src);
	if (*src == '\'')
	{
		ft_strlcpy(dst, src + 1, strlen);
		return (1);
	}
	if (*src == '"')
	{
		strcpy_interpvar(dst, src + 1, strlen, envp);
		return (1);
	}
	strcpy_interpvar(dst, src, strlen, envp);
	return (0);
}

int32_t	skipstring(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != quote && str[i] != '\0')
		i++;
	if (str[i] == quote)
		return (i + 1);
	return (i);
}
