#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p;
	unsigned char	*l;

	p = dst;
	l = (unsigned char *)src;
	if (p == 0 && l == 0)
		return ((void *)0);
	while (n > 0)
	{
		*p = *l;
		p++;
		l++;
		n--;
	}
	return (dst);
}
