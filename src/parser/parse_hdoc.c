#include "minishell.h"

static int32_t	copy_til_quote(char *dst, char *src, int32_t *i)
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

void	place_hdoc_in_node(char *dst, char *src, int32_t *i)
{
	int	j;

	j = 0;
	while (src[*i] != '\0' && is_whitespace(src[*i]) == false)
	{
		if (src[*i] == '"' || src[*i] == '\'')
			j += copy_til_quote(dst + j, src, i);
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
