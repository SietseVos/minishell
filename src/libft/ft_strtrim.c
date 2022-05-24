#include "libft.h"

int32_t	charset(const char *set, char p)
{
	while (*set)
	{
		if (*set == p)
			return (1);
		set++;
	}
	return (0);
}

int32_t	get_length(const char *str, const char *set)
{
	int32_t	len;
	int32_t	i;

	i = 0;
	len = ft_strlen(str);
	while (str[i] != 0 && charset(set, str[i]) == 1)
		i++;
	while (len != i && charset(set, str[len - 1]) == 1)
		len--;
	return (len - i);
}

char	*place_string(char *str, const char *s1, const char *set, int32_t len)
{
	char	*ret;

	ret = str;
	while (*s1 != 0 && charset(set, *s1) == 1)
		s1++;
	while (len != 0)
	{
		*str = *s1;
		str++;
		s1++;
		len--;
	}
	*str = 0;
	return (ret);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int32_t		len;
	char	*ret;

	len = get_length(s1, set);
	ret = (char *)malloc(len + 1);
	if (ret == 0)
		return (0);
	ret = place_string(ret, s1, set, len);
	return (ret);
}
