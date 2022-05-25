#include "libft.h"

int32_t	ft_isalnum(int32_t str)
{
	if ((str >= '0' && str <= '9')
		|| (str >= 'A' && str <= 'Z')
		|| (str >= 'a' && str <= 'z'))
		return (1);
	return (0);
}
