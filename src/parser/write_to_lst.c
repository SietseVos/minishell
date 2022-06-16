/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_to_lst.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 15:05:47 by svos          #+#    #+#                 */
/*   Updated: 2022/06/16 16:46:13 by svos          ########   odam.nl         */
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

int32_t	place_str_in_node(char *dst, char *src, int32_t strlen, env_vars_t *envp)
{
	int32_t	strlentmp;

	strlentmp = 0;
	while (*str != '\0' && *str != ' ')
	{
		if (*str == '"' || *str == '\'')
		{
			strlentmp += copy_til_quote(dst, src, strlen, envp);
			str += strlentmp + check_str_end(str, strlentmp, 2);
		}
		else
			strlentmp += strlen_til_space(str, envp);
		printf("strlentmp: %d\n", strlentmp);
		*strlen += strlentmp;
	}
	dst[i] = '\0';
}

int32_t	skipstring(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != quote && str[i] != '\0')
		i++;
	if (str[i] == quote)
		return (i + 1);
	return (i);
}
