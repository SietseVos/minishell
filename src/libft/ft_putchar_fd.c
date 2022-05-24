#include <unistd.h>

void	ft_putchar_fd(char c, int32_t fd)
{
	write(fd, &c, 1);
}
