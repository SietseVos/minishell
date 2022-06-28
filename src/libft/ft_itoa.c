/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 17:11:02 by svos          #+#    #+#                 */
/*   Updated: 2022/06/28 17:25:28 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int32_t	countlen(long n)
{
	int32_t	count;

	count = 0;
	if (n < 0)
		count++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*putnbr(char *ret, long n, int32_t count)
{
	if (n < 0)
		n = n * -1;
	ret = ret + count;
	*ret = 0;
	if (n == 0)
	{
		ret -= 1;
		*ret = '0';
	}
	while (n != 0)
	{
		ret--;
		*ret = n % 10 + '0';
		n = n / 10;
	}
	return (ret);
}

char	*ft_itoa(int32_t n)
{
	int32_t		count;
	char	*ret;
	long	nr;

	nr = n;
	count = countlen(nr);
	ret = malloc(count + 1);
	if (ret == 0)
		return (0);
	ret = putnbr(ret, nr, count);
	if (nr < 0)
	{
		ret--;
		*ret = '-';
	}
	return (ret);
}
