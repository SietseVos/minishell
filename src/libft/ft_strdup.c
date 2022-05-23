#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ret;

	i = 0;
	while (s1[i])
		i++;
	ret = (char *)malloc(i + 1);
	if (ret == 0)
		return (0);
	while (*s1)
	{
		*ret = *s1;
		s1++;
		ret++;
	}
	*ret = 0;
	return (ret - i);
}
