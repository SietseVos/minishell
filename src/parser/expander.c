/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 11:31:34 by svos          #+#    #+#                 */
/*   Updated: 2022/07/01 15:43:43 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int32_t	check_strmode(int32_t strmode, char c)
{
	if (c == '"' && strmode == SPACE)
		strmode = DOUBLE;
	else if (c == '"' && strmode == DOUBLE)
		strmode = SPACE;
	if (c == '\'' && strmode == SPACE)
		strmode = SINGLE;
	else if (c == '\'' && strmode == SINGLE)
		strmode = SPACE;
	return (strmode);
}

bool	check_if_hdoc(char *input, int32_t i, int32_t strmode)
{

}

int32_t	count_inputlen(char *input, t_env_vars *env)
{
	int32_t	i;
	int32_t	ret;
	int32_t	strmode;

	i = 0;
	ret = 0;
	strmode = SPACE;
	while (input[i])
	{
		strmode = check_strmode(strmode, input[i]);
		// if (input[i] == '<' && input[i+ 1] == '<' && strmode == SPACE)
		// 	i += get_hdoclen(input, i);
		if (!(input[i] == '<' && input[i + 1] == '<')
			&& (input[i] == '<' || input[i] == '>')
			&& ambigu_redirect(input, i, env) == true)
		{
			ret += envvarlen(input + i + 1, ' ');
			i += envvarlen(input + i + 1, ' ');
		}
		else if (input[i] == '$' && strmode == SPACE)
			i += interpvar_strlen(input, ' ', &ret, env);
		else if (input[i] && strmode == DOUBLE)
			i += interpvar_strlen(input, '"', &ret, env);
		else
			i++;
	}
}

char	*expander(char *input, t_env_vars *env)
{
	char	*ret;
	int32_t	size;

	size = count_inputlen(input, env);
	printf("size: %d\n", size);
}