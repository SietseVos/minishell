/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 11:31:34 by svos          #+#    #+#                 */
/*   Updated: 2022/07/04 16:50:25 by svos          ########   odam.nl         */
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
		strmode = check_strmode(strmode, input[i]);
		if (input[i] == '<' && input[i+ 1] == '<' && strmode == SPAC)
			i += get_hdoclen(input + i, &ret);
		else if (!(input[i] == '<' && input[i + 1] == '<')
			&& (input[i] == '<' || input[i] == '>')
			&& ambigu_redirect(input, i, env) == true
			&& strmode != SINGLE)
			i += get_hdoclen(input + i, &ret);
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

void	cpy_operator_space(char *dst, char *src, int32_t *i)
{
	while (is_whitespace(src[*i]) == false)
	{
		dst[*i] = src[*i];
		*i += 1;
	}
	while (is_whitespace(src[*i]) == true)
	{
		dst[*i] = src[*i];
		*i += 1;
	}
}

int32_t	uninterp_strcpy(char *dst, char *src, int32_t *i)
{
	int	j;

	j = 0;
	cpy_operator_space(dst, src, &j);
	while (src[j] != '\0' && is_whitespace(src[j]) == false)
	{
		if (src[j] == '"' || src[j] == '\'')
			hdoc_copy_til_quote(dst + j, src + j, &j);
		else
		{
			while (src[j] != '\0' && is_whitespace(src[j]) == false
				&& src[j] != '"' && src[j] != '\'')
			{
				dst[j] = src[j];
				j++;
			}
		}
	}
	while (is_whitespace(src[j]) == true)
	{
		dst[j] = src[j];
		j++;
	}
	*i += j;
	return (j);
}

void	expndr_strcpy(char *dst, char *src, t_env_vars *env)
{
	int32_t	i;
	int32_t	j;
	int32_t	strmode;

	i = 0;
	j = 0;
	strmode = SPAC;
	while (src[i])
	{
		strmode = check_strmode(strmode, src[i]);
		if (src[i] == '<' && src[i + 1] == '<' && strmode == SPAC)
			j = uninterp_strcpy(dst + j, src + i, &i);
		else if (!(src[i] == '<' && src[i + 1] == '<')
			&& (src[i] == '<' || src[i] == '>')
			&& ambigu_redirect(src, i, env) == true
			&& strmode != SINGLE)
		{
			j += uninterp_strcpy(dst + j, src + i, &i);
		}
		else if (src[i] == '$' && strmode == SPAC)
			i += place_envvar_space(dst + j, src + i, env, &j);
		else if (src[i] == '$' && strmode == DOUBLE)
			i += place_envvar_quote(dst + j, src + i, env, &j);
		else
		{
			dst[j] = src[i];
			i++;
			j++;
		}
	}
	dst[j] = '\0';
}

char	*expander(char *input, t_env_vars *env)
{
	char	*ret;
	int32_t	size;

	if (!input)
		return (NULL);
	size = count_inputlen(input, env);
	ret = malloc(size + 1);
	if (ret == NULL)
		return (NULL);
	expndr_strcpy(ret, input, env);
	return (ret);
}
