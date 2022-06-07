
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
	if (!*args)
	{
		printf("\n");
		return ;
	}
	if (is_n_flag(args[0]))
	{
		newline = false;
		while (is_n_flag(args[i]))
			i++;
	}
	else
		newline = true;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
}
