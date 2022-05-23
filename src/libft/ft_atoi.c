int	ft_atoi(const char *str)
{
	long long	sign;
	long long	count;
	int			i;

	i = 0;
	sign = 1;
	count = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		count = (*str - '0') + (count * 10);
		str++;
	}
	return (count * sign);
}
