/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_ambigu.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 10:08:00 by svos          #+#    #+#                 */
/*   Updated: 2022/06/29 12:45:15 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief - check if the string has a amiguous variable  
 * 
 * @param input - the input string
 * @param i - the index of the input string iterater
 * @param envp - environment variables
 * @param c - a single or double quote or a space
 * @return true - found ambiguous node
 * @return false - nothing suspicuos found
 */
bool	check_ambigu(char *input, int32_t i, t_env_vars *envp, char c)
{
	int32_t	len;

	len = envvarlen(input + i, c);
	while (envp)
	{
		if (ft_strncmp(envp ->str, input + i + 1, len - 1) == 0
			&& envp ->str[len - 1] == '=')
			return (false);
		envp = envp ->next;
	}
	if (input[i + len] == '\0')
		return (true);
	if (c == ' ' && (input[i + len] == ' ' || input[i + len] == '\0'))
		return (true);
	if ((c == '"' || c == '\'') && (input[i + len] == c))
	{
		i++;
		if (input[i + len] == ' ' || input[i + len] == '\0')
			return (true);
	}
	return (false);
}

/**
 * @brief - check the possbility of a ambiguous redirect
 * 
 * @param input - the input string
 * @param i - the input string index
 * @param envp - environment variables
 * @return true - found ambiguous variable
 * @return false - nothing suspicious found
 */
bool	ambigu_redirect(char *input, int32_t i, t_env_vars *envp)
{
	skip_operator_space(input, &i);
	if (input[i] != '"' && input[i] != '\'' && input[i] != '$')
		return (false);
	if (input[i] == '\0')
		return (false);
	if (input[i] == '$')
		return (check_ambigu(input, i, envp, ' '));
	else if ((input[i] == '"' || input[i] == '\'') && input[i + 1] == '$')
		return (check_ambigu(input, i + 1, envp, input[i]));
	return (false);
}

/**
 * @brief - initialize the ambiguous node
 * 
 * @param size - the size of the string in argument
 * @return t_action* - the initialized ambiguous node
 */
t_action	*create_ambigu_node(int32_t size)
{
	t_action	*ret;

	ret = malloc(sizeof(t_action));
	if (ret == NULL)
		return (NULL);
	ret->arg = malloc(sizeof(char *) * 2);
	if (ret->arg == NULL)
	{
		free(ret);
		return (NULL);
	}
	ret->arg[0] = malloc(sizeof(char) * size + 1);
	if (ret ->arg[0] == NULL)
	{
		free(ret->arg);
		free(ret);
		return (NULL);
	}
	ret->type = AMBIGU;
	ret->arg[1] = NULL;
	return (ret);
}

/**
 * @brief - make an amibuous node
 * 
 * @param input - the input string
 * @param i - a pointer to the input string iterater
 * @return t_action* - the amiguous node
 */
t_action	*found_ambigu(char *input, int32_t *i)
{
	int32_t		len;
	int32_t		j;
	t_action	*ret;

	j = 0;
	skip_operator_space(input, i);
	if (input[*i] == '"' || input[*i] == '\'')
		*i += 1;
	len = envvarlen(input + *i + 1, ' ');
	ret = create_ambigu_node(len + 1);
	if (ret == NULL)
		return (nullerr("failed to malloc ambigu node"));
	while (j <= len)
	{
		ret->arg[0][j] = input[*i];
		j++;
		*i += 1;
	}
	ret->arg[0][j] = '\0';
	if (input[*i] == '"' || input[*i] == '\'')
		*i += 1;
	while (is_whitespace(input[*i]) == true)
		*i += 1;
	return (ret);
}
