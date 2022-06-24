/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:20:58 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/24 15:57:42 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	if (str[0] == '\0')
		return (return_with_error_message(UNSET_ERROR, str, IDENT_ERROR, 1));
	while (str[i])
	{
		if (str[i] == '=' || str[i] == ' ' || str[i] == '-')
		{
			g_exit_status = 1;
			return (return_with_error_message(UNSET_ERROR, str, \
								IDENT_ERROR, true));
		}
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
	g_exit_status = 0;
	while (arg[i])
	{
		if (check_unset_error(arg[i]))
			error = 1;
		else
			remove_from_list(arg[i], list);
		i++;
	}
}
