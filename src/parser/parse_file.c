/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 10:08:12 by svos          #+#    #+#                 */
/*   Updated: 2022/06/29 14:12:35 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief - skip the operator and the whitespace that comes after that
 * 
 * @param input - the input string
 * @param i - a pointer to the input string iterater
 */
void	skip_operator_space(char *input, int32_t *i)
{
	while (is_whitespace(input[*i]) == false)
		*i += 1;
	while (is_whitespace(input[*i]) == true)
		*i += 1;
}

/**
 * @brief - initialize a file node
 * 
 * @param strlen - the length of the string
 * @param type - the type of the node 
 * @return t_action* 
 */
t_action	*create_filenode(int32_t strlen, int32_t type)
{
	t_action	*node;

	node = malloc(sizeof(t_action));
	if (node == NULL)
		return (nullerr("node malloc fail"));
	node ->arg = malloc(sizeof(char *) * 2);
	if (node ->arg == NULL)
	{
		free(node);
		return (nullerr("node arg malloc fail"));
	}
	*node ->arg = malloc(sizeof(char) * strlen + 1);
	if (node ->arg == NULL)
	{
		free(node ->arg);
		free(node);
		return (nullerr("node arg malloc fail"));
	}
	node ->arg[1] = NULL;
	node ->type = type;
	node ->next = NULL;
	return (node);
}

/**
 * @brief - make the propper redirect node
 * 
 * @param input - the input string
 * @param i - a pointer to the input iterater
 * @param type - the type that the node needs to be
 * @param envp - evironment variables
 * @return t_action* 
 */
t_action	*found_redirect(char *input, int32_t *i,
				int32_t type, t_env_vars *envp)
{
	t_action	*node;
	int32_t		strlen;

	strlen = 0;
	skip_operator_space(input, i);
	if (type == HDOC && (input[*i] == '\'' || input[*i] == '"'))
		type = HDOCQUOTE;
	else if (type == HDOC)
		type = HDOCSPACE;
	if (type == HDOCSPACE || type == HDOCQUOTE)
		read_hdoc_str(input + *i, &strlen);
	else
		read_input_str(input + *i, &strlen, envp);
	if (input[*i] == '\0' || is_operator(input[*i]) == true)
		return (nullerr("no string after space of redirect"));
	node = create_filenode(strlen, type);
	if (node == NULL)
		return (nullerr("redirect node malloc fail"));
	if (type == HDOCSPACE || type == HDOCQUOTE)
		place_hdoc_in_node(*node ->arg, input, i);
	else
		place_str_in_node(*node ->arg, input, i, envp);
	return (node);
}

/**
 * @brief - choose wich type the file node will be
 * 
 * @param input - the input string pre-chewed by the lexer
 * @param i - a pointer to the input iterater
 * @param envp - evironment varialbes
 * @return t_action* 
 */
t_action	*parse_file(char *input, int32_t *i, t_env_vars *envp)
{
	t_action	*node;

	node = NULL;
	if (check_str_end(input, *i, 2) != 2)
		return (nullerr("no string after redirect"));
	if (!(input[*i] == '<' && input[*i + 1] == '<')
		&& ambigu_redirect(input, *i, envp) == true)
		node = found_ambigu(input, i);
	else if (input[*i] == '<' && input[*i + 1] == ' ')
		node = found_redirect(input, i, INFILE, envp);
	else if (input[*i] == '>' && input[*i + 1] == ' ')
		node = found_redirect(input, i, TRUNC, envp);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		node = found_redirect(input, i, HDOC, envp);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		node = found_redirect(input, i, APPEND, envp);
	return (node);
}
