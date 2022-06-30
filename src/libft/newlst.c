/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   newlst.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 11:11:35 by svos          #+#    #+#                 */
/*   Updated: 2022/06/30 11:11:36 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*newlst(int32_t len)
{
	t_list	*newlst;
	t_list	*tmp;
	t_list	*addelem;
	int32_t	val;

	val = 0;
	newlst = malloc(sizeof(t_list));
	newlst ->content = ft_itoa(val);
	newlst ->next = 0;
	tmp = newlst;
	while (len > 0)
	{
		val++;
		addelem = malloc(sizeof(t_list));
		addelem ->content = ft_itoa(val);
		addelem ->next = 0;
		tmp ->next = addelem;
		tmp = addelem;
		len--;
	}
	return (newlst);
}
