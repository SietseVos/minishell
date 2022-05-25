
#include "minishell.h"

static void		exit_shell_error(char *str)
{
	printf("bash: exit: %s: numeric argument required\n", str);
	exit(255);
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
	return(return_value * sign);
}

static bool	check_for_wrong_argument(char *str)
{
	int32_t i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (i >= 19 || str[i] != '\0')
		return (false);
	return (false);
}

void	exit_shell(char **argument)
{
	int64_t	arg;

	if (!argument)
		exit(0);
	if (strings_in_array(argument) > 1)
	{
		printf("bash: exit: too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	if (check_for_wrong_argument(argument[0]))
		exit_shell_error(argument[0]);
	arg = ft_atoll(argument[0]);
	exit((int8_t)arg);
}
