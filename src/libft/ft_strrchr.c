char	*ft_strrchr(const char *s, int c)
{
	unsigned char	t;
	int				i;

	t = c;
	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	while (i >= 0)
	{
		if (*s == t)
			return ((char *)s);
		s--;
		i--;
	}
	return (0);
}
