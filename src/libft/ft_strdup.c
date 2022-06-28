/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:13:22 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:41 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int32_t		i;
	char	*ret;

	i = 0;
	while (s1[i])
		i++;
	ret = (char *)malloc(i + 1);
	if (ret == 0)
		return (0);
	while (*s1)
	{
		*ret = *s1;
		s1++;
		ret++;
	}
	*ret = 0;
	return (ret - i);
}
