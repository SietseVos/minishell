#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*p;

	p = str;
	while (n > 0)
	{
		*p = 0;
		p++;
		n--;
	}
}
