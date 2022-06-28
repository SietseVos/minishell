/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:12:50 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:34 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int32_t	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*f;
	const unsigned char	*d;

	f = s1;
	d = s2;
	while (n > 0)
	{
		if (*f != *d)
			return ((int)(*f - *d));
		n--;
		f++;
		d++;
	}
	return (0);
}
