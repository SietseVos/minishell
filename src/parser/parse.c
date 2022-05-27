/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:01:01 by svos          #+#    #+#                 */
/*   Updated: 2022/05/27 15:47:39 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	place_envvar(char *dst, char *src, env_vars_t *envp, int32_t *i)
{
	int32_t	varlen;

	varlen = envvarlen(src, '"');
	printf("varlen in place_envvar: %d\n", varlen);
	while (envp)
	{
		if (ft_strncmp(envp ->str, src + 1, varlen - 1) == 0 && envp ->str[varlen - 1] == '=')
		{
			printf("found environment variable in place_envvar: %s\n", envp ->str + varlen - 1);
			ft_strlcpy(dst, envp ->str + varlen + 1, strlen_quote(envp ->str + varlen) + 1);
			*i += strlen_quote(envp ->str + varlen);
			return (varlen);
		}
		envp = envp ->next;
	}
	return (varlen);
}

int32_t	read_input_str(char *str, int *strlen, env_vars_t *envp)
{
	if (*str == '"')
		return (strlen_til_quote(str + 1, strlen, '"', envp));
	else if (*str == '\'')
		return (strlen_til_quote(str + 1, strlen, '\'', envp));
	return (strlen_til_space(str, strlen, envp));
}

action_t	*determine_kind(char *input, int32_t *i, env_vars_t *envp)
{
	if (input[*i] == '<' || input[*i] == '>')
		return (parse_file(input, i, envp));
	return (parse_cmd(input, i, envp));
	// return (NULL);
}

action_t	*parser(char *input, env_vars_t *envp)
{
	int32_t			i;
	action_t	*ret;

	i = 0;
	ret = determine_kind(input, &i, envp);
	// while (input[i])
	// {
	// 	ret ->next = determine_type(input, &i);
	// }
	return (ret);
}

void	printchararr(char **toprint)
{
	int32_t	i;

	i = 0;
	printf("in character array:\n");
	while (toprint[i] != NULL)
	{
		printf("-%s-\n", toprint[i]);
		i++;
	}
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	char		*test;
	env_vars_t	*envlist;
	action_t	*inlst;

	// printf("Look mom I'm on a terminal!\n");
	create_env_vars_list(envp, &envlist);
	// printenvp(envlist);
	test = strdup("\" $USER fd dsds   fds\" fdsd");
	inlst = parser(test, envlist);
	printchararr(inlst ->arg);
	// printf("output: -%s-\n", *inlst ->arg);
	return (0);
}

// gcc parse.c parse_utils.c parse_utils_small.c parse_cmd.c parse_file.c ../env_functions/create_env_vars_list.c ../../src/libft/ft_strlcpy.c ../../src/libft/ft_strlen.c ../../src/libft/ft_strdup.c ../../src/libft/ft_strncmp.c -I ../../include/ -I ../../src/libft ../../src/libft/libft.a -fsanitize=address -g