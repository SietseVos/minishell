#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*point;

	if (*lst == 0)
		*lst = new;
	else
	{
		point32_t = *lst;
		while (point32_t ->next != 0)
			point32_t = point32_t ->next;
		point32_t ->next = new;
	}
}
