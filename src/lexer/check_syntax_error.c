/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_syntax_error.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:57:37 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 17:44:39 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function used to write a syntax error.
 * The error being written is dependant of the input string.
 * 
 * @param str Pointer to the string containing the error.
 * 
 * @param i Pointer to the index of the character causing the error.
 * 
 * @return N/A
*/
static void	write_syntax_error(char *str, int32_t *i)
{
	int32_t	char_count;
	int32_t	j;

	j = *i;
	char_count = 0;
	while (str[j] && str[*i] == str[j])
	{
		char_count++;
		j++;
	}
	if (char_count > 1)
		write_error_with_chars(TOKEN_ERROR, str[*i], str[*i], "'\n");
	else if (char_count == 1)
		write_error_with_chars(TOKEN_ERROR, str[*i], 0, "'\n");
	else if (char_count == 0)
		write(STDERR_FILENO, NL_ERROR, 57);
	g_info.exit_status = 258;
}

/**
 * Function used to skip tabs and spaces inside of a string.
 * 
 * @param str Pointer to the string containing the whitespace.
 * 
 * @param i Pointer to the index inside of the string.
 * 
 * @return N/A
*/
static void	skip_whitespace(char *str, int32_t *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		*i += 1;
}

/**
 * Function used to skip the index inside a string
 * to a special character (NULL, \, ", |, >, <)
 * 
 * @param str Pointer to the string contaning the special character.
 * 
 * @param i Pointer to the index inside of the string.
 * 
 * @return N/A
*/
static void	skip_till_special_char(char *str, int32_t *i)
{
	while (str[*i] != '\0'
		&& str[*i] != '\''
		&& str[*i] != '"'
		&& str[*i] != '|'
		&& str[*i] != '>'
		&& str[*i] != '<')
		*i += 1;
}

/**
 * Function to check if the given string contans a syntax error.
 * 
 * @param str Pointer to the string tat has to be checked.
 * 
 * @param i Pointer to the index inside the string.
 * 
 * @return - [true] contains an error - [false] string passed all checks - 
*/
static bool	check_for_error(char *str, int32_t *i)
{
	if (str[*i] == '>' || str[*i] == '<')
	{
		*i += 1;
		if (str[*i] == str[*i - 1])
			*i += 1;
		skip_whitespace(str, i);
		if (str[*i] == '>' || str[*i] == '<' || \
			str[*i] == '|' || str[*i] == '\0')
		{
			write_syntax_error(str, i);
			return (true);
		}
	}
	if (str[*i] == '|')
	{
		*i += 1;
		skip_whitespace(str, i);
		if (str[*i] == '|' || str[*i] == '\0')
		{
			write_syntax_error(str, i);
			return (true);
		}
	}
	return (false);
}

/**
 * Function to check if a given string contains a syntax error.
 * 
 * @param str pointer to the string that has to be checked.
 * 
 * @return - [true] contains an error - [false] string passed all checks - 
*/
bool	check_syntax_error(char *str)
{
	int32_t	i;

	i = 0;
	skip_whitespace(str, &i);
	if (str[i] == '|')
	{
		write_syntax_error(str, &i);
		return (true);
	}
	while (str[i])
	{
		skip_till_special_char(str, &i);
		if (str[i] == '\'' || str[i] == '"')
			skip_string(str, &i);
		else if (str[i])
		{
			if (check_for_error(str, &i))
				return (true);
		}
	}
	return (false);
}
