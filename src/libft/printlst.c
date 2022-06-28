/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printlst.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:09:36 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:09:45 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	printlst(t_list *print)
{
	while (print != 0)
	{
		printf("%s|", print ->content);
		print = print ->next;
	}
}
