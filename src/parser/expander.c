/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 11:31:34 by svos          #+#    #+#                 */
/*   Updated: 2022/07/06 12:47:29 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief - check if the string is quoted with double, single or no quotes
 * 
 * @param strmode - the current mode
 * @param c - the character in the string to be checked
 * @return int32_t - the new mode
 */
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

/**
 * @brief - check if there's an ambiguous redirect
 * 
 * @param str - the string to check
 * @param i - int iterater of str
 * @param strmode - is the string quoted with double, single or no quotes
 * @param env - environment variables
 * @return true - there's an ambiguous redirect
 * @return false - nothing special found
 */
static bool	check_if_ambigu(char *str, int32_t i,
				int32_t strmode, t_env_vars *env)
{
	if (!(str[i] == '<' && str[i + 1] == '<')
		&& (str[i] == '<' || str[i] == '>')
		&& ambigu_redirect(str, i, env) == true
		&& strmode != SINGLE)
		return (true);
	return (false);
}

/**
 * @brief - copy the input string to the new input string
 * 
 * @param dst - the destiation string
 * @param src - the source string
 * @param env - environment variables
 */
static void	expndr_strcpy(char *dst, char *src, t_env_vars *env)
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
			j += uninterp_strcpy(dst + j, src + i, &i);
		else if (check_if_ambigu(src, i, strmode, env) == true)
			j += uninterp_strcpy(dst + j, src + i, &i);
		else if (src[i] == '$' && strmode == SPAC)
			i += place_envvar_space(dst + j, src + i, env, &j);
		else if (src[i] == '$' && strmode == DOUBLE)
			i += place_envvar_quote(dst + j, src + i, env, &j);
		else
			copy_char(dst, src, &i, &j);
	}
	dst[j] = '\0';
}

/**
 * @brief - count the length of the interperted input string
 * 
 * @param input - the inputstring form the lexer
 * @param env - environment variables
 * @return int32_t - the length of the interperted input string
 */
static int32_t	count_inputlen(char *input, t_env_vars *env)
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
		if (input[i] == '<' && input[i + 1] == '<' && strmode == SPAC)
			i += get_hdoclen(input + i, &ret);
		else if (check_if_ambigu(input, i, strmode, env) == true)
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

/**
 * @brief - expands environment variables when necessary
 * 
 * @param input - input string from lexer 
 * @param env - environment variables
 * @return char* - the inputstring with expanded variables
 */
char	*expander(char *input, t_env_vars *env)
{
	char	*ret;
	int32_t	size;

	if (!input)
		return (NULL);
	size = count_inputlen(input, env);
	ret = malloc(size + 1);
	if (ret == NULL)
	{
		free(input);
		return (NULL);
	}
	expndr_strcpy(ret, input, env);
	free(input);
	return (ret);
}
