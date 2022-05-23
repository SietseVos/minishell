#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*point;

	if (*lst == 0)
		*lst = new;
	else
	{
		point = *lst;
		while (point ->next != 0)
			point = point ->next;
		point ->next = new;
	}
}
