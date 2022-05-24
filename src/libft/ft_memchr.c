#include "libft.h"

void	*ft_memchr(const void *s, int32_t c, size_t n)
{
	unsigned char		t;
	const unsigned char	*p;

	t = c;
	p = s;
	while (n > 0)
	{
		if (*p == t)
			return ((void *)p);
		n--;
		p++;
	}
	return (0);
}
