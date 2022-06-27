/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strings_in_array.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:21:03 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/27 20:42:22 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to count the amount of string inside the given array.
 * 
 * @param str Double char array containing all strings.
 * 
 * @return Amount of strings inside the given array.
*/
int32_t	strings_in_array(char **str)
{
	int32_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
