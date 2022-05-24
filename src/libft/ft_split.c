#include "libft.h"

static char	*putstr(const char *s, char c)
{
	int32_t		count;
	char	*ret;

	count = 0;
	while (s[count] != c && s[count] != 0)
		count++;
	ret = malloc(count + 1);
	if (ret == 0)
		return (0);
	while (*s != c && *s != 0)
	{
		*ret = *s;
		s++;
		ret++;
	}
	*ret = 0;
	return (ret - count);
}

static int32_t	countw(const char *s, char c)
{
	int32_t	count;

	count = 0;
	while (*s != 0)
	{
		if (*s != c)
		{
			count++;
			while (s[1] != c && s[1] != 0)
				s++;
		}
		s++;
	}
	return (count);
}

static void	free_data(char **ret, int32_t *countrev, int32_t count)
{
	while (*countrev > 0)
	{
		free(ret[*countrev]);
		*countrev -= 1;
	}
	free(ret[count]);
	free(ret);
	*countrev = count;
}

static void	putwords(char **ret, int32_t count, const char *s, char c)
{
	int32_t	countrev;

	countrev = 0;
	while (countrev < count)
	{
		ret[countrev] = putstr(s, c);
		if (ret[countrev] == 0)
			free_data(ret, &countrev, count);
		while (*s != c && *s != 0)
			s++;
		while (*s == c)
			s++;
		countrev++;
	}
}

char	**ft_split(const char *s, char c)
{
	int32_t		count;
	char	**ret;

	count = countw(s, c);
	ret = malloc((count + 1) * (sizeof(char *)));
	if (ret == 0)
		return (0);
	ret[count] = 0;
	if (count == 0)
		return (ret);
	while (*s == c)
		s++;
	putwords(ret, count, s, c);
	return (ret);
}