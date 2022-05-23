
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static bool missing_space(char *str, int i)
{
	if (i != 0 && str[i]							// check if space should be in front
		&& ((str[i] == '<' && str[i - 1] != '<')
		|| (str[i] == '>' && str[i - 1] != '>')
		|| str[i] == '|') && str[i - 1] != ' ')
		return (true);
	if (i != 0 && str[i] && str[i] != ' ' && 		// check if space should be after
		((str[i - 1] == '>' && str[i] != '>')
		|| (str[i - 1] == '<' && str[i] != '<')
		|| (str[i - 1] == '|')))
		return (true);
	return (false);
}

static int	get_missing_space_count(char *str)
{
	int	i;
	int	spaces;

	i = 0;
	spaces = 0;
	while (str[i])
	{
		if (!in_string(str[i], false) && missing_space(str, i))
			spaces++;
		i++;
	}
	in_string(str[i], true);
	return (spaces);
}

static void	fill_output(char *input, char *output)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (!in_string(input[i], false) && missing_space(input, i))
		{
			output[j] = ' ';
			j++;
		}
		output[j] = input[i];
		j++;
		i++;
	}
	in_string(input[i], true);
	output[j] = '\0';
}

char	*lexer(char	*input)
{
	int		i;
	int		spaces;
	char	*output;

	i = 0;
	spaces = get_missing_space_count(input);
	output = malloc(sizeof(char) * (ft_strlen(input) + spaces + 1));
	if (!output)
		exit(404);
	// check for syntax error (multiple >>>> in a row)
	output = check_syntax_error(output);
	fill_output(input, output);
	return (output);
}
