#include <unistd.h>
#include "libft.h"

void	ft_putstr_fd(char *s, int32_t fd)
{
	int32_t	len;

	len = ft_strlen(s);
	write(fd, s, len);
}
