/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:22:29 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/21 20:22:31 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_shell_error(char *str)
{
	exit_with_error_message("bash: exit: ", str, \
		": numeric argument required\n", 255);
}

static int64_t	ft_atoll(char *str)
{
	uint64_t	tmp;
	int64_t		return_value;
	int32_t		sign;
	int32_t		i;

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
	}
	if (tmp > __LONG_LONG_MAX__)
		exit_shell_error(str);
	return_value = tmp;
	return (return_value * sign);
}

static bool	check_for_wrong_argument(char *str, bool print)
{
	int32_t	i;

	i = 0;
	if (str[0] == '-' && str[1] != '\0')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (i >= 19 || str[i] != '\0')
	{
		if (print)
			printf("exit\n");
		return (true);
	}
	return (false);
}

static void	exit_with_g_status(bool print)
{
	if (print)
		write(STDERR_FILENO, "exit\n", 6);
	exit(g_exit_status);
}

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
	if (check_for_wrong_argument(argument[0], print))
		exit_shell_error(argument[0]);
	if (strings_in_array(argument) > 1)
	{
		write(STDERR_FILENO, "bash: exit: too many arguments\n", 32);
		g_exit_status = 1;
		return ;
	}
	arg = ft_atoll(argument[0]);
	if (print)
		write(STDERR_FILENO, "exit\n", 6);
	exit((int8_t)arg);
}
