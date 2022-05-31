/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:01:01 by svos          #+#    #+#                 */
/*   Updated: 2022/05/31 17:41:05 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

action_t	*determine_kind(char *input, int32_t *i, env_vars_t *envp)
{
	if (input[*i] == '<' || input[*i] == '>')
		return (parse_file(input, i, envp));
	return (parse_cmd(input, i, envp));
	// return (NULL);
}

action_t	*action_node_fail(action_t *tofree)
{
	action_t	*temp;

	temp = tofree;
	while (tofree)
	{
		tofree = tofree ->next;
		free(temp);
		temp = tofree;
	}
	return (nullerr("failed to make next node"));
}

action_t	*parser(char *input, env_vars_t *envp)
{
	int32_t			i;
	action_t	*ret;
	action_t	*lst;

	i = 0;
	lst = determine_kind(input, &i, envp);
	if (lst == NULL)
		return (nullerr("failed to make first node"));
	ret = lst;
	while (input[i])
	{
		lst ->next = determine_kind(input, &i, envp);
		if (lst ->next == NULL)
			return (action_node_fail(ret));
		lst = lst ->next;
	}
	lst ->next = NULL;
	///returning wrong pointer
	return (ret);
}

void	printchararr(char **toprint)
{
	int32_t	i;

	i = 0;
	printf("\033[1;34min Arguments:\033[0m\n");
	while (toprint[i] != NULL)
	{
		printf("-%s-\n", toprint[i]);
		i++;
	}
}

void	print_actions(action_t *inlst)
{
	while (inlst)
	{
		printf("\033[1;36m===== node =====\033[31m\n");
		if (inlst ->type == 0)
			printf("Type: Infile\n");
		else if (inlst ->type == 1)
			printf("Type: Outfile\n");
		else if (inlst ->type == 2)
			printf("Type: Append\n");
		else if (inlst ->type == 3)
			printf("Type: Heredoc\n");
		else if (inlst ->type == 4)
			printf("Type: Trunicate\n");
		else if (inlst ->type == 5)
			printf("Type: Pipe \n");
		else if (inlst ->type == 6)
			printf("Type: std out\n");
		else if (inlst ->type == 7)
			printf("Type: noinput\n");
		else if (inlst ->type == 8)
			printf("Type: inpipe\n");
		printchararr(inlst ->arg);
		inlst = inlst ->next;
	}
}

// int32_t	main(int32_t argc, char **argv, char **envp)
// {
// 	char		*test;
// 	env_vars_t	*envlist;
// 	action_t	*inlst;

// 	create_env_vars_list(envp, &envlist);
// 	// printenvp(envlist);
// 	test = strdup("< f fj | jfkdls jfiow nvn eiowior");
// 	inlst = parser(test, envlist);
// 	if (inlst == NULL)
// 	{
// 		printf("parsing error\n");
// 		return (0);
// 	}
// 	print_actions(inlst);
// 	return (0);
// }

// gcc parse.c read_from_str.c write_to_lst.c parse_utils_small.c parse_cmd.c parse_file.c ../env_functions/create_env_vars_list.c ../../src/libft/ft_strlcpy.c ../../src/libft/ft_strlen.c ../../src/libft/ft_strdup.c ../../src/libft/ft_strncmp.c -I ../../include/ -I ../../src/libft ../../src/libft/libft.a -fsanitize=address -g
