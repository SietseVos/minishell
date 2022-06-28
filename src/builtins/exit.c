/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:22:29 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 16:21:24 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to print the exit error on the stderr.
 * 
 * @param str Pointer to the string that caused the error.
 * 
 * @return exit with value 255
*/
static void	exit_shell_error(char *str, bool print)
{
	if (print)
		write(STDERR_FILENO, "exit\n", 6);
	exit_with_error_message("bash: exit: ", str, \
		": numeric argument required\n", 255);
}

/**
 * Function to convert a string to a long.
 * If the given string would overflow it results in an error.
 * 
 * @param str Pointer to the string that has to be converted.
 * 
 * @return Given string converted into a long.
*/
static int64_t	ft_atoll(char *str, bool print)
{
	uint64_t					tmp;
	int64_t						return_value;
	int32_t						sign;
	int32_t						i;

	i = 0;
	tmp = 0;
	sign = 1;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		tmp *= 10;
		tmp += str[i] - '0';
		i++;
		if (tmp > __LONG_LONG_MAX__ && \
			!(tmp - __LONG_LONG_MAX__ == 1 && sign == -1))
			exit_shell_error(str, print);
	}
	return_value = tmp * sign;
	return (return_value);
}

/**
 * Function to check if he given argument is not valid.
 * 
 * @param str Pointer to the string to check if it is correct.
 * 
 * @return [true] if argument is invalid [false] if correct.
*/
static bool	check_for_wrong_argument(char *str)
{
	int32_t	i;

	i = 0;
	if (str[0] == '-' && str[1] != '\0')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (i >= 21 || str[i] != '\0')
		return (true);
	return (false);
}

/**
 * Function to exit with the global exit status.
 * 
 * @param print Boolian to check if it should print
 * exit to the strderr.
 * 
 * @return Exits
*/
static void	exit_with_g_status(bool print)
{
	if (print)
		write(STDERR_FILENO, "exit\n", 6);
	exit(g_info.exit_status);
}

/**
 * Builtin function to exit the shell. 
 * 
 * @param argument Double char array containing all
 * the arguments exit has to run with.
 * 
 * @param print Boolian to check if it should print
 * exit to the strderr.
 * 
 * @return Exits
*/
void	exit_shell(char **argument, bool print)
{
	int64_t	arg;

	if (!argument)
		exit_with_g_status(print);
	if (strings_in_array(argument) == 0)
	{
		if (print)
			write(STDERR_FILENO, "exit\n", 6);
		exit(0);
	}
	if (check_for_wrong_argument(argument[0]))
		exit_shell_error(argument[0], print);
	if (strings_in_array(argument) > 1)
	{
		write(STDERR_FILENO, "bash: exit: too many arguments\n", 32);
		g_info.exit_status = 1;
		return ;
	}
	arg = ft_atoll(argument[0], print);
	if (print)
		write(STDERR_FILENO, "exit\n", 6);
	exit((int8_t)arg);
}
