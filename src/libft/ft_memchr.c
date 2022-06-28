/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:12:45 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:34 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int32_t c, size_t n)
{
	unsigned char		t;
	const unsigned char	*p;

	t = c;
	p = s;
	while (n > 0)
	{
		if (*p == t)
			return ((void *)p);
		n--;
		p++;
	}
	return (0);
}
