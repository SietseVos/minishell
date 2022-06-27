/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_env_vars_list_utils.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:53:42 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/27 20:19:04 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to copy the content from one string into another.
 * THIS FUNCTION IS NOT MEMORY SAFE.
 * 
 * @param take Pointer to the string where the info is being taken from.
 * 
 * @param place Pointer to the string where the info is being set to.
 * 
 * @return N/A
*/
static void	str_copy(char *take, char *place)
{
	int32_t	i;

	i = 0;
	while (take[i])
	{
		place[i] = take[i];
		i++;
	}
	place[i] = '\0';
}

/**
 * Function to remove the value inside the OLDPWD node.
 * 
 * @param list Pointer to the head of the environment variable list.
 * 
 * @return N/A
*/
static void	remove_old_pwd_value(env_vars_t **list)
{
	env_vars_t	*tmp;

	tmp = get_variable_node(*list, "OLDPWD=");
	if (tmp)
	{
		tmp->str[6] = '\0';
		tmp->has_value = false;
	}
}

/**
 * Function to increment the shell level value by 1.
 * 
 * @param list Pointer to the environment variable list.
 * 
 * @return - [0] Success - [-1] Malloc failed -
*/
static int32_t	increment_shell_level(env_vars_t *list)
{
	int32_t	level;
	char	*new_str;
	char	*new_num;

	list = get_variable_node(list, "SHLVL");
	if (!list)
		return (0);
	level = ft_atoi(&list->str[6]);
	level++;
	new_num = ft_itoa(level);
	if (!new_num)
		return (-1);
	new_str = malloc(sizeof(char) * (ft_strlen(new_num) + 7));
	if (!new_str)
	{
		free(new_num);
		return (-1);
	}
	str_copy("SHLVL=", new_str);
	ft_strlcat(new_str, new_num, ft_strlen(new_num) + 7);
	free(new_num);
	free(list->str);
	list->str = new_str;
	return (0);
}

/**
 * Function to remove the shell maintained variable from the list.
 * 
 * @param list Pointer to the head of the environment variable list.
 * 
 * @return N/A
*/
static void	remove_exess_from_list(env_vars_t **list)
{
	env_vars_t	*pre;
	env_vars_t	*tmp;
	env_vars_t	*next;
	int32_t		i;

	i = 0;
	remove_old_pwd_value(list);
	tmp = *list;
	while (tmp)
	{
		if (ft_strncmp("_=", tmp->str, 2) == 0)
		{
			next = tmp->next;
			free(tmp->str);
			free(tmp);
			if (i == 0)
				*list = next;
			else
				pre->next = next;
			tmp = pre;
		}
		i++;
		pre = tmp;
		tmp = tmp->next;
	}
}

/**
 * Function to cleanup the environment variable list of
 * the shell maintained variable and increase the shell level by 1.
 * 
 * @param env_head Pointer to the head of the environment variable list.
 * 
 * @return - [true] Success - [false] Malloc failed -
*/
bool	clean_env_vars_list(env_vars_t **env_head)
{
	set_env_list_bool_value(*env_head);
	remove_exess_from_list(env_head);
	if (increment_shell_level(*env_head) == -1)
		return (free_env_list_return_false(*env_head));
	return (true);
}
