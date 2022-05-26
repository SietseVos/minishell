/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:05:47 by svos          #+#    #+#                 */
/*   Updated: 2022/05/26 16:13:01 by svos          ########   odam.nl         */
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