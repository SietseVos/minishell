
#include "minishell.h"

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

void	echo(char **args)
{
	bool		newline;
	int32_t		i;

	i = 0;
	newline = true;
	if (!*args)
	{
		write(1, "\n", 1);
		return ;
	}
	if (is_n_flag(args[0]))
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
