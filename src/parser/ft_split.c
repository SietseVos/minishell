/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 09:32:36 by svos          #+#    #+#                 */
/*   Updated: 2022/05/23 11:11:06 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_split.h"

static void	free_data(char **ret, int *countrev, int count)
{
	while (*countrev > 0)
	{
		free(ret[*countrev]);
		*countrev -= 1;
	}
	free(ret[count]);
	free(ret);
	*countrev = count;
}

static int	putwords(char **ret, int words, char *s, char c)
{
	int	i;

	i = 0;
	while (i < words)
	{
		ret[i] = putstr(&s, c);
		if (ret[i] == 0)
		{
			free_data(ret, &i, words);
			return (0);
		}
		while (*s == c)
			s++;
		i++;
	}
	return (1);
}

static int	found_word(char *s, char c, int i)
{
	if (s[i] == '"')
	{
		while (!(s[i + 1] == '"' && s[i] != '\\') && s[i + 1] != 0)
			i++;
		if (s[i + 1] != 0)
			i++;
	}
	else
		while (!(s[i + 1] == '"' && s[i] != '\\')
			&& s[i + 1] != c && s[i + 1] != 0)
			i++;
	return (i);
}

static int	countw(char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != 0)
	{
		while (s[i] == '"' && s[i + 1] == '"')
			i += 1;
		if (s[i] == '"' && s[i + 1] == '\0')
			break ;
		if (s[i] != c)
		{
			i = found_word(s, c, i);
			count++;
		}
		i++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	int		words;
	char	**ret;

	words = countw(s, c);
	ret = malloc((words + 1) * (sizeof(char *)));
	if (ret == 0)
		return (0);
	ret[words] = 0;
	if (words == 0)
		return (ret);
	while (*s == c)
		s++;
	if (putwords(ret, words, s, c) == 0)
		return (0);
	return (ret);
}
