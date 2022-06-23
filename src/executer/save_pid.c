
#include "minishell.h"
#include <sys/wait.h>

child_pids_t	*get_first_pid_node(void)
{
	static child_pids_t	first;

	return (&first);
}

child_pids_t	*get_last_pid_node(void)
{
	child_pids_t	*tmp;

	tmp = get_first_pid_node();
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

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
	g_exit_status = WEXITSTATUS (return_wait);
}
