/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 10:08:06 by svos          #+#    #+#                 */
/*   Updated: 2022/07/06 12:47:10 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief - get the length of the arguments array
 * 
 * @param str - the string to be scanned
 * @return int32_t - the number of arguments in the array
 */
int32_t	get_cmdarrlen(char *str)
{
	int32_t	i;
	int32_t	ret;

	i = 0;
	ret = 0;
	while (str[i] != '\0' && is_operator(str[i]) == false)
	{
		while (str[i] != '\0')
		{
			if (is_whitespace(str[i]) == true)
			{
				while (is_whitespace(str[i]) == true)
					i++;
				break ;
			}
			else if (str[i] == '"' || str[i] == '\'')
				i += skipstring(str + i, str[i]);
			else
				i++;
		}
		ret++;
	}
	return (ret);
}

/**
 * @brief - initialize a command node
 * 
 * @param arrlen - the length of the arguments array
 * @return t_action* - the initialized node
 */
t_action	*create_cmdnode(int32_t arrlen)
{
	t_action	*node;

	node = malloc(sizeof(t_action));
	if (node == NULL)
		return (nullerr("node malloc failure"));
	node ->arg = malloc(sizeof(char *) * (arrlen + 1));
	if (node ->arg == NULL)
	{
		free(node);
		return (nullerr("node arg malloc failure"));
	}
	node->next = NULL;
	return (node);
}

/**
 * @brief - free the previous node if something goes wrong
 * 
 * @param node - the node to be freed
 * @param j - the amount of arguments
 * @return t_action* - an errorous NULL
 */
t_action	*arg_malloc_fail(t_action *node, int32_t j)
{
	j--;
	while (j >= 0)
	{
		printf("freeing %s\n", node ->arg[j]);
		free(node ->arg[j]);
		j--;
	}
	free(node ->arg);
	free(node);
	return (nullerr("failed to malloc argstring"));
}

t_action	*space_edge_case(void)
{
	t_action	*ret;

	ret = malloc(sizeof(t_action));
	if (ret == NULL)
		return (NULL);
	ret ->arg = malloc(sizeof(char *) * 2);
	if (ret ->arg == NULL)
	{
		free(ret);
		return (NULL);
	}
	ret ->arg[0] = ft_strdup("");
	if (ret ->arg[0] == NULL)
	{
		free(ret ->arg);
		free(ret ->arg[0]);
		return (NULL);
	}
	ret ->type = TOSTDOUT;
	ret ->arg[1] = NULL;
	return (ret);
}

/**
 * @brief - make a node with a command type
 * 
 * @param input - the input string pre-chewed by the lexer
 * @param i - a pointer to the input string iterater
 * @param envp - evironment variables
 * @return t_action* 
 */
t_action	*parse_cmd(char *input, int32_t *i, t_env_vars *envp)
{
	t_action	*node;
	int32_t		strlen;
	int32_t		cmdarrlen;
	int32_t		j;

	j = 0;
	if (input[*i] == '\0')
		return (space_edge_case());
	cmdarrlen = get_cmdarrlen(input + *i);
	node = create_cmdnode(cmdarrlen);
	if (node == NULL)
		return (nullerr("failed to create cmd node"));
	while (cmdarrlen > j)
	{
		strlen = 0;
		read_input_str(input + *i, &strlen, envp);
		node ->arg[j] = malloc(sizeof(char) * strlen + 1);
		if (node ->arg[j] == NULL)
			return (arg_malloc_fail(node, j));
		place_str_in_node(node ->arg[j], input, i, envp);
		j++;
	}
	node ->type = TOSTDOUT;
	node ->arg[j] = NULL;
	return (node);
}
