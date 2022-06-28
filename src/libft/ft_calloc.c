/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:10:28 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:14 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	int32_t		fill;

	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	fill = count * size;
	ptr = malloc(fill);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, fill);
	return (ptr);
}
