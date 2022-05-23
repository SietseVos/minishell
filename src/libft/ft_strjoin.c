#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*a;
	char	*ret;
	int		i;

	i = (int)ft_strlen(s2);
	a = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (a == 0)
		return (0);
	a = (char *)ft_memcpy(a, s1, ft_strlen(s1));
	ret = a;
	while (*a != 0)
		a++;
	while (i != 0)
	{
		*a = *s2;
		a++;
		s2++;
		i--;
	}
	return (ret);
}
