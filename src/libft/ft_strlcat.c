/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:13:30 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 18:52:42 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	int32_t	size;
	int32_t	ret;

	ret = ft_strlen(dst) + ft_strlen(src);
	if (dstsize < ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	len = ft_strlen(src);
	size = dstsize;
	while (*dst != 0)
	{
		size--;
		dst++;
	}
	while (size > 1 && *src != 0)
	{
		*dst = *src;
		dst++;
		src++;
		size--;
		len--;
	}
	*dst = '\0';
	return (ret);
}
