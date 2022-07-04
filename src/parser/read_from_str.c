/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_from_str.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 10:08:46 by svos          #+#    #+#                 */
/*   Updated: 2022/07/04 09:45:30 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief - get the stringlength of the exit status
 * 
 * @param strlen - pointer to the total stringlength
 * @param varlen - length of the uninterperted variable
 * 					(in this function always 2)
 * @return int32_t - see varlen
 */
int32_t	exit_status_numblen(int32_t *strlen, int32_t varlen)
{
	int32_t	cpy;

	cpy = g_info.exit_status;
	if (cpy == 0)
	{
		*strlen += 1;
		return (varlen);
	}
	while (cpy > 0)
	{
		cpy = cpy / 10;
		*strlen += 1;
	}
	return (varlen);
}

/**
 * @brief - get the stinglength of a environment variable
 * 
 * @param str - input string pointing to a $
 * @param c - singel or double quote
 * @param strlen - pointer to the total stringlength
 * @param envp - environment variables
 * @return int32_t - the stringlength of a uninterperted enviroment variable
 */
int32_t	interpvar_strlen(char *str, char c, int32_t *strlen, t_env_vars *envp)
{
	int32_t	varlen;

	varlen = envvarlen(str, c);
	if (varlen == 2 && str[1] == '?')
		return (exit_status_numblen(strlen, varlen));
	if (varlen == 1)
	{
		if (c == ' ' && (is_whitespace(str[1]) == true || str[1] == '\0'))
			*strlen += 1;
		else if (c == '"' || c == '\'')
			*strlen += 1;
		printf("varlen = 1\n");
		return (varlen);
	}
	while (envp)
	{
		if (ft_strncmp(envp ->str, str + 1, varlen - 1) == 0
			&& envp ->str[varlen - 1] == '=')
		{
			*strlen += ft_strlen(envp ->str + varlen);
			break ;
		}
		envp = envp ->next;
	}
	printf("interpvar is returning: %d\n", varlen);
	return (varlen);
}

/**
 * @brief get the length of a sting until a whitespace is found
 * 
 * @param str - input string
 * @param envp - environment variables
 * @param strlen - pointer to the stinglength
 * @return int32_t 
 */
static int32_t	strlen_til_space(char *str, t_env_vars *envp, int32_t *strlen)
{
	int32_t	i;

	i = 0;
	while (is_whitespace(str[i]) == false && str[i] != '"'
		&& str[i] != '\'' && str[i] != '\0')
	{
		if (str[i] == '$')
			i += interpvar_strlen(str + i, ' ', strlen, envp);
		else
		{
			*strlen += 1;
			i++;
		}
	}
	return (i);
}

/**
 * @brief get the length of a sting until a quote is found
 * 
 * @param str - input string
 * @param c - single or double quote
 * @param envp - environment variables
 * @param strlen - pointer to the stinglength
 * @return int32_t 
 */
static int32_t	strlen_til_quote(char *str, char c,
					t_env_vars *envp, int32_t *strlen)
{
	int32_t	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		if (c == '"' && str[i] == '$')
			i += interpvar_strlen(str + i, c, strlen, envp);
		else
		{
			*strlen += 1;
			i++;
		}
	}
	return (i);
}

/**
 * @brief - read the length of an argument
 * 
 * @param str - input string
 * @param strlen - pionter to the stringlength
 * @param envp - environment variables
 */
void	read_input_str(char *str, int *strlen, t_env_vars *envp)
{
	while (*str != '\0' && is_whitespace(*str) == false)
	{
		if (*str == '"' || *str == '\'')
		{
			str += strlen_til_quote(str + 1, *str, envp, strlen);
			if (*(str + 1) == '"' || *(str + 1) == '\'')
				str += 2;
			else
				str += 1;
		}
		else
			str += strlen_til_space(str, envp, strlen);
	}
}
