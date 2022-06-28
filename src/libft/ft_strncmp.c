/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:13:45 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:46 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int32_t	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (*a != 0 && *b != 0 && n > 0)
	{
		if (*a > *b)
			return (1);
		if (*a < *b)
			return (-1);
		n--;
		a++;
		b++;
	}
	if (ft_strlen(s1) < ft_strlen(s2) && n != 0)
		return (-1);
	if (ft_strlen(s1) > ft_strlen(s2) && n != 0)
		return (1);
	return (0);
}
