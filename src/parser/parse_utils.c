#include "minishell.h"

int32_t	check_str_end(char *str, int32_t i, int32_t n)
{
	int32_t	count;

	count = 0;
	while (count <= n && str[i + count] != '\0')
		count++;
	return (count - 1);
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
	while (ft_isalnum(str[ret]) == 1)
		ret++;
	(void) end;
	return (ret);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (true);
	return (false);
}

int32_t	skipstring(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != quote && str[i] != '\0')
		i++;
	if (str[i] == quote)
		return (i + 1);
	return (i);
}
