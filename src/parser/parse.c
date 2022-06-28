/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:01:01 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:50:04 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_action	*determine_kind(char *input, int32_t *i, t_env_vars *envp)
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

t_action	*action_node_fail(t_action *tofree)
{
	t_action	*temp;

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

t_action	*parser(char *input, t_env_vars *envp)
{
	int32_t		i;
	t_action	*ret;
	t_action	*lst;

	i = 0;
	while (is_whitespace(input[i]) == true)
		i++;
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
	if (join_split_cmds(ret) == false)
		return (nullerr("failed to join splitted commands"));
	return (ret);
}
