#include <unistd.h>

void	ft_putnbr_fd(int32_t n, int32_t fd)
{
	char	c;

	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	c = n % 10 + '0';
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	write(fd, &c, 1);
}
