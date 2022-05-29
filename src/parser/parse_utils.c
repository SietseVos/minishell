/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:05:47 by svos          #+#    #+#                 */
/*   Updated: 2022/05/27 15:59:09 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	strlen_quote(char *str)
{
	int32_t	i;
	int32_t	ret;

	i = 0;
	ret = 0;
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"' && str[i] != '\0')
	{
		ret++;
		i++;
	}
	printf("strlen of envvar in strlen_quote: %d\n", ret);
	return (ret);
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
			dst[i] = src[j];
			i++;
			j++;
		}
	}
	dst[i] = '\0';
}

void	place_str_in_node(char *dst, char *src, int32_t strlen, env_vars_t *envp)
{
	if (*src == '\'')
		ft_strlcpy(dst, src + 1, strlen);
	else if (*src == '"')
		strcpy_interpvar(dst, src + 1, strlen, envp);
	else
		strcpy_interpvar(dst, src, strlen, envp);
}

int32_t	interpvar_strlen(char *str, char c, int32_t *strlen, env_vars_t *envp)
{
	int32_t	i;
	int32_t	varlen;

	i = 0;
	varlen = envvarlen(str, c);
	while (envp)
	{
		if (ft_strncmp(envp ->str, str + 1, varlen - 1) == 0 && envp ->str[varlen - 1] == '=')
		{
			printf("found environment variable: %s\n", envp ->str + varlen - 1);
			*strlen += strlen_quote(envp ->str + varlen);
		}
		envp = envp ->next;
	}
	printf("interpvar_strlen is returning: %d\n", varlen);
	return (varlen);
}

int32_t	strlen_til_space(char *str, int32_t *strlen, env_vars_t *envp)
{
	int32_t	endskip;
	int32_t	i;

	i = 0;
	endskip = 0;
	printf("entered strlen_til_space function\n");
	while (str[i] != ' ' && str[i] != '\0')
	{
		if (str[i] == '$')
			i += interpvar_strlen(str + i, ' ', strlen, envp);
		else
		{
			*strlen += 1;
			i++;
		}
		// printf("counting char: %c in strlen_til_space\n", str[i]);
	}
	if (str[i] != '\0')
		endskip += 1;
	return (endskip);
}

int32_t	strlen_til_quote(char *str, int32_t *strlen, char c, env_vars_t *envp)
{
	int32_t	endskip;
	int32_t	i;

	i = 0;
	endskip = 0;
	while (str[i] != c && str[i] != '\0')
	{
		if (c == '"' && str[i] == '$')
			i += interpvar_strlen(str + i, c, strlen, envp);
		else
		{
			*strlen += 1;
			i++;
		}
	}
	while (endskip < 2 && str[i + endskip] != '\0')
		endskip++;
	return (endskip);
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
