/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:05:47 by svos          #+#    #+#                 */
/*   Updated: 2022/05/24 20:40:40 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	check_str_end(char *str, int32_t i, int32_t n)
{
	int32_t	count;

	count = 0;
	while (count <= n)
	{
		if (str[i + count] == '\0')
			return (count);
		count++;
	}
	return (-1);
}

int32_t	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

void	*nullerr(char *errmsg)
{
	printf("%s\n",errmsg);
	return (NULL);
}

int32_t	envvarlen(char *str, char end)
{
	int32_t	ret;

	ret = 0;
	while (str[ret] != end && str[ret] != ' ' && str[ret] != '\0')
		ret++;
	return (ret);
}

int32_t	interpvar_strlen(char *str, char c, int32_t *strlen, env_vars_t *envp)
{
	int32_t	i;
	int32_t	varlen;
	char	*tocmp;

	i = 0;
	varlen = envvarlen(str, c);
	tocmp = malloc(varlen + 1);
	if (tocmp == NULL)
		return (0);
	while (envp)
	{
		if (ft_strncmp(envp ->str, str + 1, varlen - 1))
	}
	return (0);
}

int32_t	strlen_til_space(char *str, int32_t *strlen, env_vars_t *envp)
{
	int32_t	endskip;
	int32_t	i;

	i = 0;
	endskip = 0;
	while (str[i] != ' ' && str[i] != '\0')
	{
		if (str[i] == '$')
			i += interpvar_strlen(str + i, ' ', strlen, envp);
		*strlen += 1;
		i++;
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
		*strlen += 1;
		i++;
	}
	if (c == '"')
		interpvar_strlen(str, c, strlen, envp);
	while (endskip < 2 && str[i + endskip] != '\0')
		endskip++;
	return (endskip);
}