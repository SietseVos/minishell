#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	int32_t		fill;

	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	fill = count * size;
	ptr = malloc(fill);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, fill);
	return (ptr);
}
