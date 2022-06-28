/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:13:48 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:46 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int32_t	i;
	int32_t	k;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && len != 0)
	{
		k = 0;
		while (haystack[i + k] == needle[k] && len - k != 0)
		{
			if (needle[k + 1] == '\0')
				return ((char *)&haystack[i]);
			k++;
		}
		i++;
		len--;
	}
	return (0);
}
