int32_t	ft_tolower(int32_t b)
{
	if (b >= 'A' && b <= 'Z')
		b = b + 32;
	return (b);
}
