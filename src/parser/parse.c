/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:01:01 by svos          #+#    #+#                 */
/*   Updated: 2022/06/11 15:04:35 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

action_t	*determine_kind(char *input, int32_t *i, env_vars_t *envp)
{
	// printf("pointer pointing to: -%c-\n", input[*i]);
	if (input[*i] == '|')
		return (parse_pipe(input, i));
	if (input[*i] == '<' || input[*i] == '>')
		return (parse_file(input, i, envp));
	return (parse_cmd(input, i, envp));
}

void	free_chararr(char **tofree)
{
	int	i;

	i = 0;
	while (tofree[i])
	{
		free(tofree[i]);
		i++;
	}
	free(tofree);
}

action_t	*action_node_fail(action_t *tofree)
{
	action_t	*temp;

	temp = tofree;
	while (tofree)
	{
		tofree = tofree ->next;
		free_chararr(temp ->arg);
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
	// string"newstring"anotherstring		This doesn't work
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
		printf("made a node\n");
	}
	lst ->next = NULL;
	return (ret);
}

// int32_t	main(int32_t argc, char **argv, char **envp)
// {
// 	char		*test;
// 	env_vars_t	*envlist;
// 	action_t	*inlst;

// 	create_env_vars_list(envp, &envlist);
// 	g_exit_status = 17890;
// 	// printenvp(envlist);
// 	test = strdup("< f fj | jfkdls $? nvn eiowior");
// 	inlst = parser(test, envlist);
// 	if (inlst == NULL)
// 	{
// 		printf("parsing error\n");
// 		return (0);
// 	}
// 	print_actions(inlst);
// 	return (0);
// }

// gcc parse.c read_from_str.c write_to_lst.c parse_utils_small.c parse_cmd.c parse_file.c ../env_functions/create_env_vars_list.c ../env_functions/free_env_list.c ../env_functions/get_variable_node.c ../libft/ft_strlcpy.c ../libft/ft_strlen.c ../libft/ft_strdup.c ../libft/ft_strncmp.c -I ../../include/ -I ../libft ../libft/libft.a -fsanitize=address -g
