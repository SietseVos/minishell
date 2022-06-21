/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_syntax_error.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:57:37 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/21 21:57:39 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		write_error_with_chars("bash: syntax error near unexpected token `", \
		str[*i], str[*i], "'\n");
	else if (char_count == 1)
		write_error_with_chars("bash: syntax error near unexpected token `", \
		str[*i], 0, "'\n");
	else if (char_count == 0)
		write(STDERR_FILENO, \
		"bash: syntax error near unexpected token `newline'\n", 52);
	g_exit_status = 258;
}

static void	skip_whitespace(char *str, int32_t *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		*i += 1;
}

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
