/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_strcpy.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 11:04:11 by svos          #+#    #+#                 */
/*   Updated: 2022/07/05 12:06:58 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief - copy an operater and the whitespace that comes after that
 * 
 * @param dst - the destination string
 * @param src - the source string
 * @param i - a pointer the iterater of dst and src
 */
static void	cpy_operator_space(char *dst, char *src, int32_t *i)
{
	while (is_whitespace(src[*i]) == false)
	{
		dst[*i] = src[*i];
		*i += 1;
	}
	while (is_whitespace(src[*i]) == true)
	{
		dst[*i] = src[*i];
		*i += 1;
	}
}

/**
 * @brief - copy a here doc delimiter
 * 
 * @param dst - the destination string
 * @param src - the source string
 * @param i - a pointer to the dst and src iterater
 */
static void	copy_delimiter(char *dst, char *src, int32_t *i)
{
	char	c;

	c = src[*i];
	dst[*i] = src[*i];
		*i += 1;
	while (src[*i] != '\0' && src[*i] != c)
	{
		dst[*i] = src[*i];
		*i += 1;
	}
	if (src[*i] == c)
	{
		dst[*i] = src[*i];
		*i += 1;
	}
}

/**
 * @brief - copy a sequence of whitespace
 * 
 * @param dst - the destination string
 * @param src - the source string
 * @param i - a pointer to the interater of dst and src
 */
void	copy_whitespace(char *dst, char *src, int *i)
{
	while (is_whitespace(src[*i]) == true)
	{
		dst[*i] = src[*i];
		*i += 1;
	}
}

/**
 * @brief - copy a string while not interperting variables
 * 
 * @param dst - the destination string
 * @param src - the source string
 * @param i - the iterater of the src in the previous function
 * @return int32_t - the length of the string
 */
int32_t	uninterp_strcpy(char *dst, char *src, int32_t *i)
{
	int	j;

	j = 0;
	cpy_operator_space(dst, src, &j);
	while (src[j] != '\0' && is_whitespace(src[j]) == false)
	{
		if (src[j] == '"' || src[j] == '\'')
			copy_delimiter(dst, src, &j);
		else
		{
			while (src[j] != '\0' && is_whitespace(src[j]) == false
				&& src[j] != '"' && src[j] != '\'')
			{
				dst[j] = src[j];
				j++;
			}
		}
	}
	*i += j;
	return (j);
}

/**
 * @brief - copy one character to dst
 * 
 * @param dst - the destination string
 * @param src - the source string
 * @param i - a pointer to the src interater
 * @param j - a pointer to the dst interater
 */
void	copy_char(char *dst, char *src, int32_t *i, int32_t *j)
{
	dst[*j] = src[*i];
	*i += 1;
	*j += 1;
}
