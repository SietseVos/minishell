/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:11:05 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:26:07 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
