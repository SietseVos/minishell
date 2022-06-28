/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:13:27 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:42 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*a;
	char	*ret;
	int32_t		i;

	i = (int)ft_strlen(s2);
	a = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (a == 0)
		return (0);
	a = (char *)ft_memcpy(a, s1, ft_strlen(s1));
	ret = a;
	while (*a != 0)
		a++;
	while (i != 0)
	{
		*a = *s2;
		a++;
		s2++;
		i--;
	}
	return (ret);
}
