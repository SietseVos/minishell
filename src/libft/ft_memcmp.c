#include "libft.h"

int32_t	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*f;
	const unsigned char	*d;

	f = s1;
	d = s2;
	while (n > 0)
	{
		if (*f != *d)
			return ((int)(*f - *d));
		n--;
		f++;
		d++;
	}
	return (0);
}
