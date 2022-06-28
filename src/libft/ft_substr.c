/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:13:56 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:47 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	placestr(const char *s, size_t len, char *str)
{
	int32_t	i;

	i = 0;
	while (len > 0 && *s != 0)
	{
		str[i] = *s;
		s++;
		i++;
		len--;
	}
	while (len > 0)
	{
		str[i] = 0;
		i++;
		len--;
	}
	str[i] = 0;
}

char	*ft_substr(char const *s, uint32_t start, size_t len)
{
	char	*str;

	if (len == 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	str = (char *)malloc(len + 1);
	if (str == 0)
		return (0);
	placestr(&s[start], len, str);
	return (str);
}
