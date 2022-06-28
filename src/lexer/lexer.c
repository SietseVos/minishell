/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:59:56 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 19:17:21 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This function checks if there is a missing space
 * in front of behind the current index.
 * 
 * @param str Pointer to the string that has to be checked for spaces.
 * 
 * @param i The index whis has to be checked for.
 * 
 * @return - [true] a space is missing -
 * [false] there is no space missing at the current index.
*/
static bool	missing_space(char *str, int32_t i)
{
	if (i != 0 && str[i] && str[i - 1] != ' '
		&& ((str[i] == '<' && str[i - 1] != '<')
			|| (str[i] == '>' && str[i - 1] != '>')
			|| (str[i] == '|')))
		return (true);
	if (i != 0 && str[i] && str[i] != ' '
		&& ((str[i - 1] == '>' && str[i] != '>')
			|| (str[i - 1] == '<' && str[i] != '<')
			|| (str[i - 1] == '|')))
		return (true);
	return (false);
}

/**
 * Function to return the amount of missing spaces within the given string.
 * 
 * @param str String that has to be checked for missing spaces.
 * 
 * @return - [missing space count] -
*/
static int32_t	get_missing_space_count(char *str)
{
	int32_t	i;
	int32_t	spaces;

	i = 0;
	spaces = 0;
	while (str[i])
	{
		if (!in_string(str[i], false) && missing_space(str, i))
			spaces++;
		i++;
	}
	in_string(str[i], true);
	return (spaces);
}

/**
 * This function copies the input string into the output string
 * and adds spaces where needed.
 * 
 * @param input Pointer to the string that needs to be copied.
 * 
 * @param output Pointer to a string that needs to b filled with
 * the input string with added spaces.
 * 
 * @return N/A
*/
static void	fill_output(char *input, char *output)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (!in_string(input[i], false) && missing_space(input, i))
		{
			output[j] = ' ';
			j++;
		}
		output[j] = input[i];
		j++;
		i++;
	}
	in_string(input[i], true);
	output[j] = '\0';
}

/**
 * Function used to tokenize the given input string on spaces
 * whilst also checking fot syntax errors.
 * 
 * @param input String containing the input that has to be converted.
 * 
 * @return - [output] correct string with spaces at the right places -
 * [NULL] syntax error / malloc failed -
*/
char	*lexer(char	*input)
{
	int32_t	spaces;
	char	*output;

	if (check_syntax_error(input))
		return (NULL);
	spaces = get_missing_space_count(input);
	output = malloc(sizeof(char) * (ft_strlen(input) + spaces + 1));
	if (!output)
	{
		write(STDERR_FILENO, "Malloc failed\n", 15);
		free(input);
		return (NULL);
	}
	fill_output(input, output);
	free(input);
	return (output);
}
