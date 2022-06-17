/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_to_lst.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:05:47 by svos          #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/06/17 19:14:19 by rvan-mee      ########   odam.nl         */
=======
/*   Updated: 2022/06/17 16:54:09 by svos          ########   odam.nl         */
>>>>>>> 95104ddd117677fada08d169a9d54e723bac0848
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	interp_exit_status(int32_t varlen, char *dst, int32_t *i)
{
	int32_t	j;
	int32_t	cpy;
	
	j = 0;
	cpy = g_exit_status;
	if (cpy == 0)
	{
		dst[j] = '0';
		*i += 1;
		return (varlen);
	}
	while (cpy > 0)
	{
		cpy = cpy / 10;
		j++;
	}
	cpy = g_exit_status;
	j--;
	while (cpy > 0)
	{
		dst[j] = cpy % 10 + '0';
		cpy = cpy / 10;
		j--;
		*i += 1;
	}
	return (varlen);
}

int32_t	place_envvar(char *dst, char *src, env_vars_t *envp, int32_t *i)
{
	int32_t	varlen;

	varlen = envvarlen(src, '"');
	if (varlen == 2 && src[1] == '?')
		return (interp_exit_status(varlen, dst, i));
	while (envp)
	{
		if (ft_strncmp(envp ->str, src + 1, varlen - 1) == 0 && envp ->str[varlen - 1] == '=')
		{
			ft_strlcpy(dst, envp ->str + varlen, ft_strlen(envp ->str + varlen) + 1);
			*i += ft_strlen(envp ->str + varlen);
			return (varlen);
		}
		envp = envp ->next;
	}
	return (varlen);
}

void	strcpy_interpvar(char *dst, char *src, int32_t strlen, env_vars_t *envp)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	j = 0;
	while (src[j] != '\0' && strlen > i + 1)
	{
		if (src[j] == '$')
			j += place_envvar(dst + i, src + j, envp, &i);
		else
		{
			dst[i] = src[j];
			i++;
			j++;
		}
	}
	dst[i] = '\0';
}

int32_t	len_to_next_arg(char *str, char delim)
{
	int32_t	ret;
	int32_t	endskip;

	ret = 0;
	endskip = 0;
	if (delim == ' ')
	{
		while (str[ret] != delim && str[ret] != '\t' && str[ret] != '\0')
			ret++;
		while ((str[ret + endskip] == delim || str[ret + endskip] == '\t') && str[ret + endskip] != '\0')
			endskip++;
	}
	else
	{
		while (str[ret] != delim && str[ret] != '\0')
			ret++;
		while (str[ret + endskip] == delim && str[ret + endskip] != '\0')
			endskip++;
	}
	while (str[ret + endskip] == ' ' && str[ret + endskip] != '\0')
		endskip++;
	return (ret + endskip);
}

// int32_t	place_str_in_node(char *dst, char *src, int32_t strlen, env_vars_t *envp)
// {
// 	if (*src == '\'')
// 	{
// 		ft_strlcpy(dst, src + 1, strlen);
// 		return (len_to_next_arg(src + 1, '\'') + 1);
// 	}
// 	if (*src == '"')
// 	{
// 		strcpy_interpvar(dst, src + 1, strlen, envp);
// 		return (len_to_next_arg(src + 1, '"') + 1);
// 	}
// 	strcpy_interpvar(dst, src, strlen, envp);
// 	return (len_to_next_arg(src, ' '));
// }

int32_t	copy_til_quote(char *dst, char *src, int32_t *i, env_vars_t *envp)
{
	char	c;
	int32_t	j; 

	c = src[*i];
	*i += 1;
	j = 0;
	while (src[*i] != '\0' && src[*i] != c)
	{
		if (src[*i] == '$' && c == '"')
			*i += place_envvar(dst + j, src + *i, envp, &j);
		else
		{
			printf("copying: -%c- on %p and j: %d\n", src[*i], &dst[j], j);
			dst[j] = src[*i];
			*i += 1;
			j++;
		}
	}
	if (src[*i] == c)
		*i += 1;
	// *i += check_str_end(src + *i, 0, 1);
	return (j);
}

int32_t	copy_til_space(char *dst, char *src, int32_t *i, env_vars_t *envp)
{
	int32_t	j; 

	j = 0;
	while (src[*i] != '\0' && is_whitespace(src[*i]) == false)
	{
		// printf("in copy til space, reading: %c\n", src[*i]);
		if (src[*i] == '$')
			*i += place_envvar(dst + j, src + *i, envp, &j);
		else
		{
			dst[j] = src[*i];
			*i += 1;
			j++;
		}
	}
	return (j);
}

void	place_str_in_node(char *dst, char *src, int32_t *i, env_vars_t *envp)
{
	int	j;

	j = 0;
	while (src[*i] != '\0' && is_whitespace(src[*i]) == false)
	{
		printf("Processign string: %s\n", src + *i);
		if (src[*i] == '"' || src[*i] == '\'')
		{
			j += copy_til_quote(dst + j, src, i, envp);
			// str += strlentmp + check_str_end(str, strlentmp, 2);
		}
		else
			j += copy_til_space(dst + j, src, i, envp);
	}
	dst[j] = '\0';
	while (is_whitespace(src[*i]) == true)
		*i += 1;
}

int32_t	skipstring(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != quote && str[i] != '\0')
		i++;
	if (str[i] == quote)
	{
		printf("skipped string with plus 1, returning: %d\n", i + 1);
		return (i + 1);
	}
	printf("skipped string, returning: %d\n", i);
	return (i);
}
