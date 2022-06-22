#include "minishell.h"

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

int32_t	look_for_other_types(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			return (PIPE);
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				return (HDOC);
			return (TRUNC);
		}
		if (str[i] == '\'' || str[i] == '"')
			i += skipstring(str + i + 1, str[i]);
	}
	return (TOSTDOUT);
}

action_t	*create_cmdnode(int32_t arrlen)
{
	action_t	*node;

	node = malloc(sizeof(action_t));
	if (node == NULL)
		return (nullerr("node malloc failure"));
	node ->arg = malloc(sizeof(char *) * (arrlen + 1));
	if (node ->arg == NULL)
	{
		free(node);
		return (nullerr("node arg malloc failure"));
	}
	return (node);
}

action_t	*arg_malloc_fail(action_t *node, int32_t j)
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

action_t	*parse_cmd(char *input, int32_t *i, env_vars_t *envp)
{
	action_t	*node;
	int32_t		strlen;
	int32_t		cmdarrlen;
	int32_t		j;

	j = 0;
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
