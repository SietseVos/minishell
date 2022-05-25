/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:01:01 by svos          #+#    #+#                 */
/*   Updated: 2022/05/25 09:54:27 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	int32_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

action_t	*create_node(int32_t strlen, char *str, int32_t type)
{
	action_t	*node;

	node = malloc(sizeof(action_t));
	if (node == NULL)
		return (nullerr("node malloc fail"));
	node ->arg = malloc(sizeof(char) * strlen + 1);
	if (node ->arg == NULL)
	{
		free(node);
		return (nullerr("node arg malloc fail"));
	}
	node ->type = type;
	return (node);
}

action_t	*found_redirect(char *input, int32_t *i, int32_t type, env_vars_t *envp)
{
	action_t	*node;
	int32_t		strlen;
	int32_t		endskip;

	strlen = 0;
	while (input[*i] != ' ')
		*i += 1;
	*i += 1;
	if (input[*i] == ' ')
		endskip = strlen_til_space(input + *i, &strlen, envp);
	if (input[*i] == '"')
	{
		*i += 1;
		endskip = strlen_til_quote(input + *i, &strlen, '"', envp);
	}
	if (input[*i] == '\'')
	{
		*i += 1;
		endskip = strlen_til_quote(input + *i, &strlen, '\'', envp);
	}
	if (strlen == 0 || is_operator(input[*i]) == true)
		return (nullerr("no string after space of redirect"));
	node = create_node(strlen, input + *i, type);
	if (node == NULL)
		return (nullerr("redirect node malloc fail"));
	if (input[*i - 1] == '\'')
		ft_strlcpy(node ->arg, input + *i, strlen + 1);
	else
		interpert_str(node ->arg, input + *i, strlen + 1);
	*i = *i + strlen + endskip;
	return (node);
}

action_t	*parse_file(char *input, int32_t *i, env_vars_t *envp)
{
	action_t	*node;

	if (check_str_end(input, *i, 2) >= 0)
		return (nullerr("no string after redirect"));
	if (input[*i] == '<' && input[*i + 1] == ' ')
		node = found_redirect(input, i, INFILE, envp);
	if (input[*i] == '>' && input[*i + 1] == ' ')
		node = found_redirect(input, i, OUTFILE, envp);
	if (input[*i] == '<' && input[*i + 1] == '<')
		node = found_redirect(input, i, HDOC, envp);
	if (input[*i] == '>' && input[*i + 1] == '>')
		node = found_redirect(input, i, APPEND, envp);
	return (node);
}

action_t	*determine_type(char *input, int32_t *i, env_vars_t *envp)
{
	if (input[*i] == '<' || input[*i] == '>')
		return (parse_file(input, i, envp));
	// return (parse_cmd(input, i));
	return (NULL);
}

action_t	*parser(char *input, env_vars_t *envp)
{
	int32_t			i;
	action_t	*ret;

	i = 0;
	ret = determine_type(input, &i, envp);
	// while (input[i])
	// {
	// 	ret ->next = determine_type(input, &i);
	// }
	return (ret);
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	char test;
	env_vars_t	**envlist;
	action_t	*inlst;

	create_env_vars_list(envp, envlist);
	test = strdup("< fjjklds");
	inlst = parser(test, *envlist);
	return (0);
}

// gcc parse.c parse_utils.c ../env_functions/create_env_vars_list.c ../../src/libft/ft_strlcpy.c ../../src/libft/ft_strlen.c ../../src/libft/ft_strdup.c ../../src/libft/ft_strncmp.c -I ../../include/ -I ../../src/libft ../../src/libft/libft.a -fsanitize=address -g