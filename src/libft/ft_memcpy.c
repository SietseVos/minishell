/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:12:52 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:35 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p;
	unsigned char	*l;

	p = dst;
	l = (unsigned char *)src;
	if (p == 0 && l == 0)
		return ((void *)0);
	while (n > 0)
	{
		*p = *l;
		p++;
		l++;
		n--;
	}
	return (dst);
}
