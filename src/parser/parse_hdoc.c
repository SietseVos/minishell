/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_hdoc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 10:08:17 by svos          #+#    #+#                 */
/*   Updated: 2022/07/04 15:17:35 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief copy a string unlill a quote has been found
 * 
 * @param dst - the destination string
 * 				(the user has to make sure enough memory is allocated)
 * @param src - the source string
 * @param i - a pointer to the source string iterater
 * @return int32_t - the length of the string
 */
int32_t	hdoc_copy_til_quote(char *dst, char *src, int32_t *i)
{
	char	c;
	int32_t	j;

	c = src[*i];
	*i += 1;
	j = 0;
	while (src[*i] != '\0' && src[*i] != c)
	{
		dst[j] = src[*i];
		*i += 1;
		j++;
	}
	if (src[*i] == c)
		*i += 1;
	return (j);
}

/**
 * @brief - place a heredoc string in a string
 * 
 * @param dst - the destination string
 * 				(the user has to make sure enough memory is allocated)
 * @param src - the source string
 * @param i - a pointer to the source string iterater
 */
void	place_hdoc_in_node(char *dst, char *src, int32_t *i)
{
	int	j;

	j = 0;
	while (src[*i] != '\0' && is_whitespace(src[*i]) == false)
	{
		if (src[*i] == '"' || src[*i] == '\'')
			j += hdoc_copy_til_quote(dst + j, src, i);
		else
		{
			while (src[*i] != '\0' && is_whitespace(src[*i]) == false
				&& src[*i] != '"' && src[*i] != '\'')
			{
				dst[j] = src[*i];
				*i += 1;
				j++;
			}
		}
	}
	dst[j] = '\0';
	while (is_whitespace(src[*i]) == true)
		*i += 1;
}

/**
 * @brief - read the string untill a whitespace has been found
 * 
 * @param str - the string from where to read
 * @param c - a single or double quote
 * @param strlen - a pointer to the total stringlength
 * @return int32_t - the length of the string
 */
static int32_t	strlen_til_space(char *str, int32_t *strlen)
{
	int32_t	i;

	i = 0;
	while (is_whitespace(str[i]) == false && str[i] != '"'
		&& str[i] != '\'' && str[i] != '\0')
	{
		*strlen += 1;
		i++;
	}
	return (i);
}

/**
 * @brief - read the string untill a quote has been found
 * 
 * @param str - the string from where to read
 * @param c - a single or double quote
 * @param strlen - a pointer to the total stringlength
 * @return int32_t - the length of the string
 */
static int32_t	strlen_til_quote(char *str, char c, int32_t *strlen)
{
	int32_t	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		*strlen += 1;
		i++;
	}
	return (i);
}

/**
 * @brief - get the stringlength of a heredoc delimiter
 * 
 * @param str - the string from where to read
 * @param strlen - a pointer to the total stringlength
 */
void	read_hdoc_str(char *str, int *strlen)
{
	while (*str != '\0' && is_whitespace(*str) == false)
	{
		if (*str == '"' || *str == '\'')
		{
			str += strlen_til_quote(str + 1, *str, strlen);
			if (*(str + 1) == '"' || *(str + 1) == '\'')
				str += 2;
			else
				str += 1;
		}
		else
			str += strlen_til_space(str, strlen);
	}
}
