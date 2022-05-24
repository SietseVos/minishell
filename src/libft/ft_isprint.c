int32_t	ft_isprint(int32_t str)
{
	if (str < ' ' || str > '~')
		return (0);
	return (1);
}
