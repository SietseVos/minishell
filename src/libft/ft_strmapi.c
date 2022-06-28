/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:13:39 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:45 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	uint32_t	i;
	char		*str;

	i = 0;
	str = malloc(ft_strlen(s) + 1);
	if (str == 0)
		return (0);
	while (s[i])
	{
		str[i] = f(i, (char)s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
