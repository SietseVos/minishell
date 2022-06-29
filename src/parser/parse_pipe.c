/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_pipe.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 10:08:29 by svos          #+#    #+#                 */
/*   Updated: 2022/06/29 11:56:48 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief - create a pipe node
 * 
 * @param input - the input string which is a pipe character
 * @param i - the index of str
 * @return t_action* - a pipe node
 */
t_action	*parse_pipe(char *input, int32_t *i)
{
	t_action	*ret;

	ret = malloc(sizeof(t_action));
	if (ret == NULL)
		return (nullerr("failed to malloc pipe node"));
	ret->type = PIPE;
	ret->arg = NULL;
	*i += 1;
	while (input[*i] != '\0' && is_whitespace(input[*i]))
		*i += 1;
	return (ret);
}
