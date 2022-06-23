/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:01:01 by svos          #+#    #+#                 */
/*   Updated: 2022/06/23 13:23:34 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

action_t	*determine_kind(char *input, int32_t *i, env_vars_t *envp)
{
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
	int32_t		i;
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
	printf("actions before merge\n");
	print_actions(ret);
	printf("\n\n");
	if (join_split_cmds(ret) == false)
		return (nullerr("failed to join splitted commands"));
	return (ret);
}

// fix this: ls			-la
// add new node type for incorrect env variable as redirect