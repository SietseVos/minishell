/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:13:35 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:45 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int32_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}
