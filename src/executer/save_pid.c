/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_pid.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:08:38 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 17:18:29 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

/**
 * Function to get the address of the first (staticaly allocated)
 * child_pids_t node.
 * 
 * @return - [first child_pids_t node] -
*/
child_pids_t	*get_first_pid_node(void)
{
	static child_pids_t	first;

	return (&first);
}

/**
 * Function to the the final child_pids_t node inside the list.
 * 
 * @return - [last child_pids_t node] -
*/
child_pids_t	*get_last_pid_node(void)
{
	child_pids_t	*tmp;

	tmp = get_first_pid_node();
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/**
 * Function to add a new pid to the child_pids_t list.
 * 
 * @param new_pid The pid to be added to the list.
 * 
 * @return - [0] success - [-1] malloc failed -
*/
int32_t	save_pid(pid_t new_pid)
{
	child_pids_t	*new;
	child_pids_t	*last;

	new = malloc(sizeof(child_pids_t));
	if (!new)
		return (-1);
	new->pid = new_pid;
	new->next = NULL;
	last = get_last_pid_node();
	last->next = new;
	return (0);
}

/**
 * Function that is used to reset the child_pids_t list after use.
 * 
 * @return N/A
*/
void	reset_pid(void)
{
	child_pids_t	*tmp;
	child_pids_t	*next;

	tmp = get_first_pid_node();
	tmp = tmp->next;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	tmp = get_first_pid_node();
	tmp->next = NULL;
}

/**
 * Function used to set the global g_info.exit_status to the exit status
 * of the last executed fork.
 * 
 * @return N/A
*/
void	set_exit_status_and_wait(void)
{
	child_pids_t	*node;
	child_pids_t	*last_child;
	int32_t			return_wait;

	node = get_first_pid_node();
	last_child = get_last_pid_node();
	if (!node->next)
		return ;
	waitpid(last_child->pid, &return_wait, 0);
	while (node && node->next)
	{
		wait(NULL);
		node = node->next;
	}
	reset_pid();
	if (!WIFSIGNALED (return_wait))
		g_info.exit_status = WEXITSTATUS (return_wait);
}
