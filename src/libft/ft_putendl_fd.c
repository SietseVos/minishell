#include <unistd.h>
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}
