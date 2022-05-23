int	ft_tolower(int b)
{
	if (b >= 'A' && b <= 'Z')
		b = b + 32;
	return (b);
}
