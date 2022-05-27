#include "minishell.h"

int32_t	get_cmdarrlen(char *str)
{
	int32_t	i;
	int32_t	ret;

	i = 0;
	ret = 0;
	while (is_operator(str[i]) == false && str[i] != '\0')
	{
		while (str[i] != '\0')
		{
			if (str[i] == ' ')
			{
				i++;
				break;
			}
			else if (str[i] == '"' || str[i] == '\'')
			{
				// printf("i before skipstring: %d, char: %c\n", i, str[i]);
				i += skipstring(str, str[i]);
				// printf("i after skipstring: %d, char: %c\n", i, str[i]);
			}
			else
				i++;
		}
		ret++;
	}
	printf("wordcount: %d\n", ret);
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

int32_t	determine_cmdtype(char *input, char **last_str)
{
	*last_str = NULL;
	if (*input == '|')
		return (PIPE);
	if (*input == '<')
		return (look_for_other_types(input));
	if (*input == '>')
	{
		if (*input + 1 == '>')
			return (HDOC);
		return (TRUNC);
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

action_t	*parse_cmd(char *input, int32_t *i, env_vars_t *envp)
{
	action_t	*node;
	int32_t		strlen;
	int32_t		cmdarrlen;
	int32_t		endskip;
	int32_t		j;

	strlen = 0;
	j = 0;
	cmdarrlen = get_cmdarrlen(input + *i);
	node = create_cmdnode(cmdarrlen);
	if (node == NULL)
		return (nullerr("failed to create cmd node"));
	while (cmdarrlen > j)
	{
		printf("looped 'the' loop\n");
		endskip = read_input_str(input + *i, &strlen, envp);
		printf("endskip: %d\n", endskip);
		node ->arg[j] = malloc (sizeof(char) * strlen);
		if (node ->arg[j] == NULL)
			return (nullerr("node argstring malloc failure"));
		// make malloc failure function
		place_str_in_node(node ->arg[j], input + *i, strlen + 1, envp);
		printf("ending string: %c\n", input[*i + strlen]);
		*i = *i + strlen + endskip;
		j++;
	}
	node ->type = determine_cmdtype(input + *i, &node ->arg[j]);
	return (node);
}
