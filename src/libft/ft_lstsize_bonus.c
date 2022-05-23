#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*point;

	count = 0;
	point = lst;
	while (point != 0)
	{
		point = point->next;
		count++;
	}
	return (count);
}
