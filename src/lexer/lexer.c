/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:59:56 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/21 22:00:01 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	missing_space(char *str, int32_t i)
{
	if (i != 0 && str[i] && str[i - 1] != ' '
		&& ((str[i] == '<' && str[i - 1] != '<')
			|| (str[i] == '>' && str[i - 1] != '>')
			|| (str[i] == '|')))
		return (true);
	if (i != 0 && str[i] && str[i] != ' '
		&& ((str[i - 1] == '>' && str[i] != '>')
			|| (str[i - 1] == '<' && str[i] != '<')
			|| (str[i - 1] == '|')))
		return (true);
	return (false);
}

static int32_t	get_missing_space_count(char *str)
{
	int32_t	i;
	int32_t	spaces;

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
	int32_t	i;
	int32_t	j;

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
	int32_t	spaces;
	char	*output;

	if (check_syntax_error(input))
		return (NULL);
	spaces = get_missing_space_count(input);
	output = malloc(sizeof(char) * (ft_strlen(input) + spaces + 1));
	if (!output)
		exit(404);
	fill_output(input, output);
	free(input);
	return (output);
}
