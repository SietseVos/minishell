/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:20:58 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 17:50:04 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to remove a given argument from the environment variable list.
 * 
 * @param arg Pointer to the string containing the argument 
 * that has to be removed.
 * 
 * @return N/A
*/
static void	remove_from_list(char *arg, t_env_vars **list)
{
	t_env_vars	*pre;
	t_env_vars	*tmp;
	t_env_vars	*next;
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

/**
 * Function to check if the given inut is correct.
 * 
 * @param str Pointer to the string that needs to be checked.
 * 
 * @return - [false] input correct - [true] Input incorrect -
*/
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
			g_info.exit_status = 1;
			return (return_with_error_message(UNSET_ERROR, str, \
								IDENT_ERROR, true));
		}
		i++;
	}
	return (false);
}

/**
 * Builtin function to unset and remove values insid
 * the environment variable list.
 * 
 * @param arg Double char array containing all the arguments for unset. 
 * 
 * @param list Pointer to the head of the environment variable list.
 * 
 * @return N/A
*/
void	unset(char **arg, t_env_vars **list)
{
	int32_t	error;
	int32_t	i;

	i = 0;
	error = 0;
	g_info.exit_status = 0;
	while (arg[i])
	{
		if (!check_unset_error(arg[i]))
			remove_from_list(arg[i], list);
		i++;
	}
}
