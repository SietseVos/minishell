/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:12:19 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:32 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*new;

	if (lst == 0)
		return (0);
	ret = malloc(sizeof(t_list));
	ret ->content = f(lst ->content);
	ret ->next = 0;
	lst = lst ->next;
	new = ret;
	while (lst != 0)
	{
		new ->next = ft_lstnew(f(new ->content));
		if (new == 0)
		{
			ft_lstclear(&ret, del);
			return (0);
		}
		new = new ->next;
		lst = lst ->next;
	}
	return (ret);
}
