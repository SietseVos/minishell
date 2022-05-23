int	ft_isprint(int str)
{
	if (str < ' ' || str > '~')
		return (0);
	return (1);
}
