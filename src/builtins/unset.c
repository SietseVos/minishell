
#include "minishell.h"

static void	remove_from_list(char *arg, env_vars_t **list)
{
	env_vars_t	*pre;
	env_vars_t	*tmp;
	env_vars_t	*next;
	int32_t		i;

	i = 0;
	tmp = *list;
	while (tmp)
	{
		if (ft_strncmp(arg, tmp->str, ft_strlen(arg)) == 0)
		{
			next = tmp->next;
			free(tmp->str);
			free(tmp);
			if (i == 0)
				*list = next;
			else
				pre->next = next;
			break ;
		}
		i++;
		pre = tmp;
		tmp = tmp->next;
	}
}

static bool	check_unset_error(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (return_with_error_message("bash: unset: `", str, \
								"': not a valid identifier\n", true));
		i++;
	}
	return (false);
}

void	unset(char **arg, env_vars_t **list)
{
	int32_t	error;
	int32_t	i;

	i = 0;
	error = 0;
	while (arg[i])
	{
		if (check_unset_error(arg[i]))
			error = 1;
		else
			remove_from_list(arg[i], list);
		i++;
	}
	if (error)
		g_exit_status = 1;
	else
		g_exit_status = 0;
}
