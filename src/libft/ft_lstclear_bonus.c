#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst != 0)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		del(tmp ->content);
		free(tmp);
	}
}
