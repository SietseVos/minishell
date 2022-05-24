#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	int32_t		size;
	int32_t		ret;

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
