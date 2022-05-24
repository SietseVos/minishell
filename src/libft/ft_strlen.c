#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int32_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}
