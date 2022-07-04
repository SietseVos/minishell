/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_pid.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:08:38 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 17:49:28 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <signal.h>

/**
 * Function to get the address of the first (staticaly allocated)
 * t_child_pids node.
 * 
 * @return - [first t_child_pids node] -
*/
t_child_pids	*get_first_pid_node(void)
{
	static t_child_pids	first;

	return (&first);
}

/**
 * Function to the the final t_child_pids node inside the list.
 * 
 * @return - [last t_child_pids node] -
*/
t_child_pids	*get_last_pid_node(void)
{
	t_child_pids	*tmp;

	tmp = get_first_pid_node();
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/**
 * Function to add a new pid to the t_child_pids list.
 * 
 * @param new_pid The pid to be added to the list.
 * 
 * @return - [0] success - [-1] malloc failed -
*/
int32_t	save_pid(pid_t new_pid)
{
	t_child_pids	*new;
	t_child_pids	*last;

	new = malloc(sizeof(t_child_pids));
	if (!new)
		return (-1);
	new->pid = new_pid;
	new->next = NULL;
	last = get_last_pid_node();
	last->next = new;
	return (0);
}

/**
 * Function that is used to reset the t_child_pids list after use.
 * 
 * @return N/A
*/
void	reset_pid(void)
{
	t_child_pids	*tmp;
	t_child_pids	*next;

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
	t_child_pids	*node;
	t_child_pids	*last_child;
	int32_t			return_wait;

	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 1;
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
