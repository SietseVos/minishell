#include "libft.h"

int32_t	ft_lstsize(t_list *lst)
{
	int32_t		count;
	t_list	*point;

	count = 0;
	point32_t = lst;
	while (point32_t != 0)
	{
		point32_t = point->next;
		count++;
	}
	return (count);
}
