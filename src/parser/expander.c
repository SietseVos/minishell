/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 11:31:34 by svos          #+#    #+#                 */
/*   Updated: 2022/07/04 10:18:14 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int32_t	check_strmode(int32_t strmode, char c)
{
	if (c == '"' && strmode == SPAC)
		strmode = DOUBLE;
	else if (c == '"' && strmode == DOUBLE)
		strmode = SPAC;
	if (c == '\'' && strmode == SPAC)
		strmode = SINGLE;
	else if (c == '\'' && strmode == SINGLE)
		strmode = SPAC;
	return (strmode);
}

void	loop_til_char(char *str, int32_t *i, char c)
{
	while (str[*i] != c && str[*i] != '\0')
		*i += 1;
}

int32_t	get_hdoclen(char *input, int32_t *ret)
{
	int32_t	len;

	len = 0;
	skip_operator_space(input, &len);
	while (input[len])
	{
		if (input[len] == '"' || input[len] == '\'')
		{
			loop_til_char(input, &len, input[len]);
			len++;
		}
		else
			loop_til_char(input, &len, ' ');
	}
	*ret += len;
	return (len);
}

int32_t	count_inputlen(char *input, t_env_vars *env)
{
	int32_t	i;
	int32_t	ret;
	int32_t	strmode;

	i = 0;
	ret = 0;
	strmode = SPAC;
	while (input[i])
	{
		printf("strmode: %d\n", strmode);
		strmode = check_strmode(strmode, input[i]);
		if (input[i] == '<' && input[i+ 1] == '<' && strmode == SPAC)
			i += get_hdoclen(input + i, &ret);
		else if (!(input[i] == '<' && input[i + 1] == '<')
			&& (input[i] == '<' || input[i] == '>')
			&& ambigu_redirect(input, i, env) == true
			&& strmode != SINGLE)
		{
			printf("found ambiguous\n");
			ret += envvarlen(input + i + 1, ' ');
			i += envvarlen(input + i + 1, ' ');
		}
		else if (input[i] == '$' && strmode == SPAC)
			i += interpvar_strlen(input + i, ' ', &ret, env);
		else if (input[i] == '$' && strmode == DOUBLE)
			i += interpvar_strlen(input + i, '"', &ret, env);
		else
		{
			ret++;
			i++;
		}
	}
	return (ret);
}

char	*expander(char *input, t_env_vars *env)
{
	// char	*ret;
	int32_t	size;

	if (!input)
		return (NULL);
	size = count_inputlen(input, env);
	printf("size: %d\n", size);
	return (NULL);
}

