/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:12:26 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:12:40 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int32_t	ft_lstsize(t_list *lst)
{
	int32_t		count;
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
