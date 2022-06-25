#include "minishell.h"

int32_t	count_cmdfrags(action_t *lst)
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

void	move_to_next_pipe(action_t **lst)
{
	while (*lst != NULL && (*lst)->type != PIPE)
		*lst = (*lst)->next;
	if (*lst != NULL)
		*lst = (*lst)->next;
}

bool	merge_cmdfrags(action_t *lst, int32_t cmdfrags)
{
	action_t	*cmdnode;
	action_t	**prevnextptr;

	cmdnode = lst;
	while (cmdnode->next != NULL && cmdnode->type != TOSTDOUT
		&& cmdnode->type != PIPE)
	{
		cmdnode = cmdnode->next;
	}
	lst = cmdnode ->next;
	prevnextptr = &cmdnode->next;
	while (cmdfrags > 1 && lst != NULL)
	{
		// printf("lst is pointing to: %s\n", lst->arg[0]);
		// printf("current actions:\n");
		// print_actions(cmdnode);
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

bool	join_split_cmds(action_t *lst)
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
