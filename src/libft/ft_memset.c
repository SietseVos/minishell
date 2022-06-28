/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:12:58 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:36 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int32_t c, size_t n)
{
	unsigned char	*p;

	p = str;
	while (n > 0)
	{
		*p = c;
		p++;
		n--;
	}
	return (str);
}
