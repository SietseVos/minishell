#include "minishell.h"

int32_t	check_str_end(char *str, int32_t i, int32_t n)
{
	int32_t	count;

	count = 0;
	while (count <= n)
	{
		if (str[i + count] == '\0')
			return (count);
		count++;
	}
	return (-1);
}

int32_t	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

int32_t	envvarlen(char *str, char end)
{
	int32_t	ret;

	ret = 1;
	if (str[ret] == '?')
		return (2);
	if (end == ' ')
	{
		while (str[ret] != ' ' && str[ret] != '\t' && str[ret] != ' ' && str[ret] != '\0' && str[ret] != '$' && str[ret] != '=' && str[ret] != '?')
			ret++;
	}
	else
		while (str[ret] != end && str[ret] != ' ' && str[ret] != '\0' && str[ret] != '$' && str[ret] != '=' && str[ret] != '?')
			ret++;
	return (ret);
}
