#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(src);
	while (*src != 0)
	{
		if (i + 1 < dstsize)
		{
			*dst = *src;
			dst++;
		}
		i++;
		src++;
	}
	if (dstsize != 0)
		*dst = '\0';
	return (len);
}
