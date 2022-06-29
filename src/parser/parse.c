/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 10:07:34 by svos          #+#    #+#                 */
/*   Updated: 2022/06/29 11:01:01 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief decide whether the program needs to make a pipe, file, or command node
 * 
 * @param input - input string
 * @param i - pointer to string iterater
 * @param envp - environment variables
 * @return t_action* - a pearl to be joined to a neckles
 */
t_action	*determine_kind(char *input, int32_t *i, t_env_vars *envp)
{
	if (input[*i] == '|')
		return (parse_pipe(input, i));
	if (input[*i] == '<' || input[*i] == '>')
		return (parse_file(input, i, envp));
	return (parse_cmd(input, i, envp));
}

/**
 * @brief free a array of strings
 * 
 * @param tofree - string array that needs to be freed
 */
void	free_chararr(char **tofree)
{
	int	i;

	i = 0;
	while (tofree[i])
	{
		free(tofree[i]);
		i++;
	}
	free(tofree);
}

/**
 * @brief free previous nodes if something goes wrong
 * 
 * @param tofree - the list that needs to be freed
 * @return t_action* - an errorous NULL
 */
t_action	*action_node_fail(t_action *tofree)
{
	t_action	*temp;

	temp = tofree;
	while (tofree)
	{
		tofree = tofree ->next;
		free_chararr(temp ->arg);
		free(temp);
		temp = tofree;
	}
	return (nullerr("failed to make next node"));
}

/**
 * @brief This is where the great parsing adventure begins
 * 
 * @param input - string pre-chewed by lexer
 * @param envp - environment variables
 * @return t_action* - list with all the actions
 */
t_action	*parser(char *input, t_env_vars *envp)
{
	int32_t		i;
	t_action	*ret;
	t_action	*lst;

	i = 0;
	while (is_whitespace(input[i]) == true)
		i++;
	lst = determine_kind(input, &i, envp);
	if (lst == NULL)
		return (nullerr("failed to make first node"));
	ret = lst;
	while (input[i])
	{
		lst ->next = determine_kind(input, &i, envp);
		if (lst ->next == NULL)
			return (action_node_fail(ret));
		lst = lst ->next;
	}
	lst ->next = NULL;
	if (join_split_cmds(ret) == false)
		return (nullerr("failed to join splitted commands"));
	return (ret);
}
