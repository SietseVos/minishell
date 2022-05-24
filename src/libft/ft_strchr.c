char	*ft_strchr(const char *s, int32_t c)
{
	unsigned char	t;

	t = c;
	while (*s && *s != 0)
	{
		if (*s == t)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (0);
}
