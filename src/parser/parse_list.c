/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 10:08:23 by svos          #+#    #+#                 */
/*   Updated: 2022/06/29 12:04:50 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief - count how many command fragments there are
 * 
 * @param lst - the main action list
 * @return int32_t - the number of command fragments
 */
int32_t	count_cmdfrags(t_action *lst)
{
	int32_t	ret;

	ret = 0;
	while (lst != NULL && lst ->type != PIPE)
	{
		if (lst ->type == TOSTDOUT)
			ret++;
		lst = lst->next;
	}
	return (ret);
}

/**
 * @brief - move the pointer the list after the next pipe node
 * 
 * @param lst - the main action list
 */
void	move_to_next_pipe(t_action **lst)
{
	while (*lst != NULL && (*lst)->type != PIPE)
		*lst = (*lst)->next;
	if (*lst != NULL)
		*lst = (*lst)->next;
}

/**
 * @brief - select nodes that need to me merged
 * 
 * @param lst - the main action list
 * @param cmdfrags - how many command fragments there are between the pipes
 * @return true - merge successfull
 * @return false - merge not successfull
 */
bool	merge_cmdfrags(t_action *lst, int32_t cmdfrags)
{
	t_action	*cmdnode;
	t_action	**prevnextptr;

	cmdnode = lst;
	while (cmdnode->next != NULL && cmdnode->type != TOSTDOUT
		&& cmdnode->type != PIPE)
		cmdnode = cmdnode->next;
	lst = cmdnode ->next;
	prevnextptr = &cmdnode->next;
	while (cmdfrags > 1 && lst != NULL)
	{
		if (lst->type == TOSTDOUT)
		{
			if (merge_nodes(cmdnode, &lst, prevnextptr) == false)
				return (false);
			cmdfrags--;
		}
		else
		{
			prevnextptr = &lst->next;
			lst = lst->next;
		}
	}
	return (true);
}

/**
 * @brief - join command nodes that have been separated from eachother
 * 
 * @param lst - the main action list
 * @return true - the merge was successfull
 * @return false - the merge was not successfull
 */
bool	join_split_cmds(t_action *lst)
{
	int32_t	cmdfrags;

	while (lst != 0)
	{
		cmdfrags = count_cmdfrags(lst);
		if (merge_cmdfrags(lst, cmdfrags) == false)
			return (boolerr("failed to merge command fragments"));
		move_to_next_pipe(&lst);
	}
	return (true);
}
