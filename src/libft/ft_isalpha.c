#include "libft.h"

int32_t	ft_isalpha(int32_t str)
{
	if ((str >= 'a' && str <= 'z')
		|| (str >= 'A' && str <= 'Z'))
		return (1);
	return (0);
}
