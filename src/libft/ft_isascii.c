#include "libft.h"

int32_t	ft_isascii(int32_t p)
{
	if (p < 0 || p > 127)
		return (0);
	return (1);
}
