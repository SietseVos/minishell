/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_strlen.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 09:34:22 by svos          #+#    #+#                 */
/*   Updated: 2022/07/05 11:26:14 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief - loop through the string until a char has bee found
 * 
 * @param str - the string to be iterated over
 * @param i - the iterater of str
 * @param c - the character that represents the end of the string
 */
static void	loop_til_char(char *str, int32_t *i, char c)
{
	while (str[*i] != c && str[*i] != '\0')
		*i += 1;
}

/**
 * @brief - Get the length of the here doc delimiter
 * 
 * @param input - the input string pointing to "<<
 * @param ret - the string iterater
 * @return int32_t - the length of the here doc sequence
 */
int32_t	get_hdoclen(char *input, int32_t *ret)
{
	int32_t	len;

	len = 0;
	skip_operator_space(input, &len);
	while (input[len] && input[len] != ' ')
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
