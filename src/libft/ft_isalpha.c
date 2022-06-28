/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:10:49 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:25 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int32_t	ft_isalpha(int32_t str)
{
	if ((str >= 'a' && str <= 'z')
		|| (str >= 'A' && str <= 'Z'))
		return (1);
	return (0);
}
