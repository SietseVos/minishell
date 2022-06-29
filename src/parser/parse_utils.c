/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 10:08:34 by svos          #+#    #+#                 */
/*   Updated: 2022/06/29 11:55:04 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief - check where the string has a null-terminator
 * 
 * @param str - the string to be checked
 * @param i - the index of str
 * @param n - the amount of charaters need to be checked
 * @return int32_t - the index of where the null character was
 */
int32_t	check_str_end(char *str, int32_t i, int32_t n)
{
	int32_t	count;

	count = 0;
	while (count <= n && str[i + count] != '\0')
		count++;
	return (count - 1);
}

/**
 * @brief - check if a character is a operator or not
 * 
 * @param c - the character to be checked
 * @return int32_t - result of the check
 */
int32_t	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

/**
 * @brief - get the length of an uninterperted variable
 * 
 * @param str - string containing the variable and str[0] == '$'
 * @param end - unnecessary variable
 * @return int32_t - length of uninterperted variable
 */
int32_t	envvarlen(char *str, char end)
{
	int32_t	ret;

	ret = 1;
	if (str[ret] == '?')
		return (2);
	while (ft_isalnum(str[ret]) == 1)
		ret++;
	(void) end;
	return (ret);
}

/**
 * @brief - check if a character is whitespace or not
 * 
 * @param c - the cararter to be checked
 * @return true - a whitespace has been found
 * @return false - no whitespace has bee found
 */
bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (true);
	return (false);
}

/**
 * @brief - skip a quoted string
 * 
 * @param str - string where the skip needs to be placed
 * @param quote - single or double quote
 * @return int32_t - the length to be skipped
 */
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
