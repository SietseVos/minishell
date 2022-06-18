
#include "minishell.h"

bool	run_if_builtin_child(info_t *info)
{
	if (ft_strncmp(info->action->arg[0], "cd", 3) == 0)
		cd(&info->action->arg[1], info->list);
	else if (ft_strncmp(info->action->arg[0], "echo", 5) == 0)
		echo(&info->action->arg[1]);
	else if (ft_strncmp(info->action->arg[0], "env", 4) == 0)
		env(info->list);
	else if (ft_strncmp(info->action->arg[0], "exit", 5) == 0)
		exit_shell(&info->action->arg[1], false);
	else if (ft_strncmp(info->action->arg[0], "export", 7) == 0)
		export(&info->action->arg[1], info->list);
	else if (ft_strncmp(info->action->arg[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(info->action->arg[0], "unset", 6) == 0)
		unset(&info->action->arg[1], &info->list);
	else
		return (false);
	return (true);
}

int32_t	run_builtin_no_pipe(action_t *actions, env_vars_t *list)
{
	bool		return_value_b;
	int32_t		return_value_i;

	return_value_i = 0;
	return_value_b = true;
	pop_nodes_till_command(actions);
	if (ft_strncmp(actions->arg[0], "cd", 3) == 0)
		return_value_i = cd(&actions->arg[1], list);
	else if (ft_strncmp(actions->arg[0], "echo", 5) == 0)
		echo(&actions->arg[1]);
	else if (ft_strncmp(actions->arg[0], "env", 4) == 0)
		env(list);
	else if (ft_strncmp(actions->arg[0], "exit", 5) == 0)
	{
		free_env_list(list);
		exit_shell(&actions->arg[1], true);
	}
	else if (ft_strncmp(actions->arg[0], "export", 7) == 0)
		return_value_b = export(&actions->arg[1], list);
	else if (ft_strncmp(actions->arg[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(actions->arg[0], "unset", 6) == 0)
		unset(&actions->arg[1], &list);
	if (return_value_i == -1 || return_value_b == false)
		return (-1);
	return (0);
}
