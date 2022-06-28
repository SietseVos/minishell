/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   in_string.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:57:43 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 19:06:28 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * this function resets the double_quote and single_quote
 * intergers back to 0 and then returns return_v
 * 
 * @param double_quote Pointer to the int which will be set to 0.
 * 
 * @param single_quote Pointer to the int which will be set to 0.
 * 
 * @param return_v Int used as the return value of this function.
 * 
 * @return - [return_v] -
*/
static int32_t	reset_and_return(int32_t *double_quote, \
					int32_t *single_quote, bool return_v)
{
	if (double_quote)
		*double_quote = 0;
	if (single_quote)
		*single_quote = 0;
	return (return_v);
}

/**
 * This function can be called inside of a loop to check if the
 * current passed character is within quotes.
 * 
 * @param c Current character within a string.
 * 
 * @param reset Clears the internal data to make sure
 * it wont mess with the next call.
 * 
 * @return - [true] the current character is within quotes -
 * [false] the current character is outside of quotes -
*/
bool	in_string(char c, bool reset)
{
	static int32_t	double_quote = 0;
	static int32_t	single_quote = 0;

	if (reset)
		return (reset_and_return(&double_quote, &single_quote, false));
	if (c != '\'' && c != '"' && !double_quote && !single_quote)
		return (false);
	if (c == '\'' && !double_quote)
	{
		single_quote++;
		if (single_quote == 2)
			return (reset_and_return(NULL, &single_quote, true));
		return (false);
	}
	else if (c == '"' && !single_quote)
	{
		double_quote++;
		if (double_quote == 2)
			return (reset_and_return(&double_quote, NULL, true));
		return (false);
	}
	return (true);
}

/**
 * This function can be used to skip a string within a string.
 * 
 * @param str the string containing the string.
 * 
 * @param i Pointer to the index within thee string.
*/
void	skip_string(char *str, int32_t *i)
{
	if (in_string(str[*i], false))
		*i += 1;
	while (str[*i] && in_string(str[*i], false))
		*i += 1;
	in_string(str[*i], true);
}
