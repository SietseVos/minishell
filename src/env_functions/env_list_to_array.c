/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_to_array.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:50:26 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 17:50:04 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to copy the content from one string into another.
 * THIS FUNCTION IS NOT MEMORY SAFE.
 * 
 * @param take Pointer to the string where the info is being taken from.
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
 * Function to free the given double char array till the given index.
 * 
 * @param array Double char array that needs freeing.
 * @param index The max index (+ 1) to be freed.
 * 
 * @return - [NULL] -
*/
char	**free_array_till_index(char **array, int32_t index)
{
	int32_t	i;

	i = 0;
	while (i < index)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	if (array)
		free(array);
	return (NULL);
}

/**
 * Function to get the size of the given linked list.
 * 
 * @param env_list Pointer to the environment variable list.
 * 
 * @return - [list size] size of the list -
*/
int32_t	env_list_size(t_env_vars *env_list)
{
	int32_t	i;

	i = 0;
	while (env_list)
	{
		env_list = env_list->next;
		i++;
	}
	return (i);
}

/**
 * Function to convert the environment variable linked list
 * back into a double char array.
 * 
 * @param env_list Pointer to the environment variable list.
 * 
 * @return - [new array] Success - [NULL] Malloc failed -
*/
char	**env_list_to_array(t_env_vars *env_list)
{
	t_env_vars	*list;
	char		**env_array;
	int32_t		i;

	i = 0;
	list = env_list;
	env_array = malloc(sizeof(char *) * (env_list_size(env_list) + 1));
	if (!env_array)
		return (NULL);
	while (i < env_list_size(env_list))
	{
		env_array[i] = malloc(sizeof(char) * ft_strlen(list->str) + 1);
		if (!env_array[i])
			return (free_array_till_index(env_array, i));
		str_copy(list->str, env_array[i]);
		i++;
		list = list->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
