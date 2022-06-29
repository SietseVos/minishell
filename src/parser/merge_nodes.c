/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   merge_nodes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 10:07:50 by svos          #+#    #+#                 */
/*   Updated: 2022/06/29 14:05:58 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief - count how many strings a string array has
 * 
 * @param arr - the array to be counted
 * @return int32_t - the amount of strings
 */
int32_t	count_strings(char **arr)
{
	int32_t	count;

	count = 0;
	while (*arr != NULL)
	{
		count++;
		arr++;
	}
	return (count);
}

/**
 * @brief - duplicate the arrays to the return array
 * 
 * @param ret - the final return array
 * @param arr1 - array 1
 * @param arr2 - array  2
 * @return true - function successfull
 * @return false - function not successfull
 */
bool	dup_strs_to_chararr(char **ret, char **arr1, char **arr2)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	j = 0;
	while (arr1[i] != NULL)
	{
		ret[i] = ft_strdup(arr1[i]);
		if (ret[i] == NULL)
			return (boolerr("dup chararr string malloc fail"));
		i++;
	}
	while (arr2[j] != NULL)
	{
		ret[i] = ft_strdup(arr2[j]);
		if (ret[i] == NULL)
			return (boolerr("dup chararr string malloc fail"));
		i++;
		j++;
	}
	ret[i] = NULL;
	return (true);
}

/**
 * @brief - join two string arrays
 * 
 * @param arr1 - array 1
 * @param arr2 - array 2
 * @return char** - joined array
 */
char	**join_chararrs(char **arr1, char **arr2)
{
	int32_t	strcount;
	char	**ret;

	strcount = count_strings(arr1) + count_strings(arr2);
	ret = malloc(sizeof(char *) * (strcount + 1));
	if (ret == NULL)
		return (nullerr("failed to malloc ret for join_chararrs"));
	if (dup_strs_to_chararr(ret, arr1, arr2) == false)
	{
		free_double_array(ret);
		return (NULL);
	}
	return (ret);
}

/**
 * @brief - merge two nodes
 * 
 * @param dst - destination node
 * @param src - node that will be put in dst and after that removed
 * @param prevnextptr - the next pointer of the previous node
 * @return true - merge successfull
 * @return false - something blew up
 */
bool	merge_nodes(t_action *dst, t_action **src, t_action **prevnextptr)
{
	char		**fragdst;
	char		**fragsrc;
	t_action	*freeme;

	fragdst = dst->arg;
	fragsrc = (*src)->arg;
	freeme = *src;
	dst->arg = join_chararrs(fragdst, fragsrc);
	if (dst->arg == NULL)
		return (NULL);
	*prevnextptr = (*src)->next;
	*src = (*src)->next;
	free_double_array(fragdst);
	free_double_array(fragsrc);
	free(freeme);
	return (true);
}
