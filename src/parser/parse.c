/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:01:01 by svos          #+#    #+#                 */
/*   Updated: 2022/05/25 17:38:09 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

action_t	*create_filenode(int32_t strlen, char *str, int32_t type)
{
	action_t	*node;

	node = malloc(sizeof(action_t));
	if (node == NULL)
		return (nullerr("node malloc fail"));
	node ->arg = malloc(sizeof(char *) * 2);
	if (node ->arg == NULL)
	{
		free(node);
		return (nullerr("node arg malloc fail"));
	}
	*node ->arg = malloc(sizeof(char) * strlen + 1);
	if (node ->arg == NULL)
	{
		free(node ->arg);
		free(node);
		return (nullerr("node arg malloc fail"));
	}
	node ->arg[1] = NULL;
	node ->type = type;
	return (node);
}

int32_t	place_envvar(char *dst, char *src, env_vars_t *envp, int32_t *i)
{
	int32_t	varlen;

	varlen = envvarlen(dst, '"');
	while (envp)
	{
		if (ft_strncmp(envp ->str, src + 1, varlen - 1) && envp ->str[varlen - 1] == '=')
		{
			ft_strlcpy(dst, envp ->str + varlen, ft_strlen(envp ->str + varlen) + 1);
			*i += ft_strlen(envp ->str + varlen);
			return (varlen);
		}
		envp = envp ->next;
	}
	return (0);
}

void	strcpy_interpvar(char *dst, char *src, int32_t strlen, env_vars_t *envp)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	j = 0;
	printf("entered strcpu_interpvar function\n");
	printf("strlen in strcpy_interpvar function: %d\n", strlen);
	while (src[j] != '\0' && strlen > i + 1)
	{
		if (src[j] == '$')
			j += place_envvar(dst, src, envp, &i);
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
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
	if (input[*i] == '"')
	{
		*i += 1;
		endskip = strlen_til_quote(input + *i, &strlen, '"', envp);
	}
	else if (input[*i] == '\'')
	{
		*i += 1;
		endskip = strlen_til_quote(input + *i, &strlen, '\'', envp);
	}
	else
		endskip = strlen_til_space(input + *i, &strlen, envp);
	printf("current char: %c, strlen: %d, endskip: %d\n", input[*i], strlen, endskip);
	if (input[*i] == '\0' || is_operator(input[*i]) == true)
		return (nullerr("no string after space of redirect"));
	node = create_filenode(strlen, input + *i, type);
	if (node == NULL)
		return (nullerr("redirect node malloc fail"));
	if (input[*i - 1] == '\'')
	{
		printf("entering ft_strlcpy\n");
		ft_strlcpy(*node ->arg, input + *i, strlen + 1);
	}
	else
		strcpy_interpvar(*node ->arg, input + *i, strlen + 1, envp);
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
	char		*test;
	env_vars_t	*envlist;
	action_t	*inlst;

	// printf("Look mom I'm on a terminal!\n");
	create_env_vars_list(envp, &envlist);
	test = strdup("< fj jklds");
	inlst = parser(test, envlist);
	printf("output: %s\n", *inlst ->arg);
	return (0);
}

// gcc parse.c parse_utils.c ../env_functions/create_env_vars_list.c ../../src/libft/ft_strlcpy.c ../../src/libft/ft_strlen.c ../../src/libft/ft_strdup.c ../../src/libft/ft_strncmp.c -I ../../include/ -I ../../src/libft ../../src/libft/libft.a -fsanitize=address -g