/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_putstr.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 09:52:42 by svos          #+#    #+#                 */
/*   Updated: 2022/03/16 10:05:11 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_split.h"

static void	insertstr(char **s, char *ret, int i, int count)
{
	while (i < count)
	{
		if (i < count - 1)
		{
			if (*(*s + 1) == '"' && **s == '\\')
			{
				count--;
				*s += 1;
			}
		}
		ret[i] = **s;
		i++;
		*s += 1;
	}
	if (*s + 1 != 0)
		*s += 1;
	ret[i] = 0;
}

static int	charcount(char **s, char c, int count)
{
	if (*s[count] == '"')
	{
		while (!(*(*s + count + 1) == '"' && *(*s + count) != '\\') && *(*s + count + 1) != 0)
			count++;
		*s += 1;
	}
	else
	{
		while (!(*(*s + count + 1) == '"' && *(*s + count) != '\\')
			&& *(*s + count + 1) != c && *(*s + count + 1) != 0)
			count++;
		count++;
	}
	return (count);
}

char	*putstr(char **s, char c)
{
	int		count;
	char	*ret;
	int		i;

	count = 0;
	i = 0;
	while (**s == '"' && *(*s + 1) == '"')
		*s = *s + 2;
	count = charcount(s, c, count);
	ret = malloc(count + 1);
	if (ret == 0)
		return (0);
	insertstr(s, ret, i, count);
	return (ret);
}
