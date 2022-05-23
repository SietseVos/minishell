#include "libft.h"

static void	movestr(unsigned char *p, unsigned char *l, size_t len)
{
	if (p < l)
	{
		while (len > 0)
		{
			*p = *l;
			p++;
			l++;
			len--;
		}
	}
	else
	{
		p = p + len - 1;
		l = l + len - 1;
		while (len > 0)
		{
			*p = *l;
			p--;
			l--;
			len--;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p;
	unsigned char	*l;

	p = dst;
	l = (unsigned char *)src;
	if (p == 0 && l == 0)
		return ((void *)0);
	movestr(p, l, len);
	return (dst);
}
