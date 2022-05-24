int32_t	ft_toupper(int32_t a)
{
	if (a >= 'a' && a <= 'z')
		a = a - 32;
	return (a);
}
