/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:05:47 by svos          #+#    #+#                 */
/*   Updated: 2022/05/24 17:32:16 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str_end(char *str, int i, int n)
{
	int	count;

	count = 0;
	while (count <= n)
	{
		if (str[i + count] == '\0')
			return (count);
		count++;
	}
	return (-1);
}

int	is_operator(char c)
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

int	envvarlen(char *str, char end)
{
	int	ret;

	ret = 0;
	while (str[ret] != end && str[ret] != ' ' && str[ret] != '\0')
		ret++;
	return (ret);
}

int	interpvar_strlen(char *str, char c, int *strlen, env_vars_t *envp)
{
	int		i;
	int		varlen;
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

int	strlen_til_space(char *str, int *strlen, env_vars_t *envp)
{
	int	endskip;
	int	i;

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

int	strlen_til_quote(char *str, int *strlen, char c, env_vars_t *envp)
{
	int	endskip;
	int	i;

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