#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int32_t	i;
	int32_t	k;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && len != 0)
	{
		k = 0;
		while (haystack[i + k] == needle[k] && len - k != 0)
		{
			if (needle[k + 1] == '\0')
				return ((char *)&haystack[i]);
			k++;
		}
		i++;
		len--;
	}
	return (0);
}
