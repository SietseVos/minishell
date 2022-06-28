/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:12:55 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:35 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	movestr(unsigned char *p, unsigned char *l, size_t len)
{
	if (p < l)
	{
		while (len > 0)
		{
			*p = *l;
			p++;
			l++;
			len--;
		}
	}
	else
	{
		p = p + len - 1;
		l = l + len - 1;
		while (len > 0)
		{
			*p = *l;
			p--;
			l--;
			len--;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p;
	unsigned char	*l;

	p = dst;
	l = (unsigned char *)src;
	if (p == 0 && l == 0)
		return ((void *)0);
	movestr(p, l, len);
	return (dst);
}
