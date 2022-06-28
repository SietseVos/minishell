/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:22:42 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 16:21:24 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to check if a given string can pass
 * as a -n flag.
 * 
 * @param str Pointer to the string to check.
 * 
 * @return - [true] Given string is an -n flag - 
 * 
 * [false] Given string is  not an -n flag -
*/
static bool	is_n_flag(char *str)
{
	int32_t	i;

	if (!str)
		return (false);
	if (str[0] != '-')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/**
 * Builtin function to output the given arguments
 * to the stdout. If an -n flag is given it won't output a newline.
 * Sets the exit status to 0.	
 * 
 * @param args Double char array containing all arguments.
 * 
 * @return N/A
*/
void	echo(char **args)
{
	bool		newline;
	int32_t		i;

	i = 0;
	newline = true;
	g_info.exit_status = 0;
	if (args[0] && is_n_flag(args[0]))
	{
		newline = false;
		while (is_n_flag(args[i]))
			i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
}
