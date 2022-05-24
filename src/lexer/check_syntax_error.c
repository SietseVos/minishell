
#include "minishell.h"

static void	write_syntax_error(char *str, int *i)
{
	int	char_count;
	int	j;

	j = *i;
	char_count = 0;
	while (str[j] && str[*i] == str[j])
	{
		char_count++;
		j++;
	}
	if (char_count > 1)
		printf("bash: syntax error near unexpected token `%c%c'\n", str[*i], str[*i]);
	else
		printf("bash: syntax error near unexpected token `%c'\n", str[*i]);
	// set exit value??
}

static void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		*i += 1;
}

static void	skip_till_special_char(char *str, int *i)
{
	while (str[*i] != '\0'
		&& str[*i] != '\''
		&& str[*i] != '"'
		&& str[*i] != '|'
		&& str[*i] != '>'
		&& str[*i] != '<')
		*i += 1;
}

static bool	check_for_error(char *str, int *i)
{
	if (str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
	{
		*i += 1;
		if (str[*i] == str[*i - 1] && str[*i] != '|')
			*i += 1;
		skip_spaces(str, i);
		if (str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
		{
			write_syntax_error(str, i);
			return (true);
		}
	}
	return (false);
}

bool	check_syntax_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		skip_till_special_char(str, &i);
		if (str[i] == '\'' || str[i] == '"')
			skip_string(str, &i);
		else if (str[i])
		{
			if (check_for_error(str, &i))
				return (true);
		}
	}
	return (false);
}
