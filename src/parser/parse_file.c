#include "minishell.h"

action_t	*create_filenode(int32_t strlen, int32_t type)
{
	action_t	*node;

	node = malloc(sizeof(action_t));
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

action_t	*found_redirect(char *input, int32_t *i,
				int32_t type, env_vars_t *envp)
{
	action_t	*node;
	int32_t		strlen;

	strlen = 0;
	while (is_whitespace(input[*i]) == false)
		*i += 1;
	while (is_whitespace(input[*i]) == true)
		*i += 1;
	if (type == HDOC && (input[*i] == '\'' || input[*i] == '"'))
		type = HDOCQUOTE;
	else if (type == HDOC)
		type = HDOCSPACE;
	read_input_str(input + *i, &strlen, envp);
	if (input[*i] == '\0' || is_operator(input[*i]) == true)
		return (nullerr("no string after space of redirect"));
	node = create_filenode(strlen, type);
	if (node == NULL)
		return (nullerr("redirect node malloc fail"));
	place_str_in_node(*node ->arg, input, i, envp);
	return (node);
}

bool	check_ambigu(char *input, int32_t i, env_vars_t *envp, char c)
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

bool	ambigu_redirect(char *input, int32_t i, env_vars_t *envp)
{
	while (is_whitespace(input[i]) == false)
		i += 1;
	while (is_whitespace(input[i]) == true)
		i += 1;
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

action_t	*create_ambigu_node(int32_t size)
{
	action_t	*ret;

	ret = malloc(sizeof(action_t));
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

action_t	*found_ambigu(char *input, int32_t *i)
{
	int32_t		len;
	int32_t		j;
	action_t	*ret;

	j = 0;
	while (is_whitespace(input[*i]) == false)
		*i += 1;
	while (is_whitespace(input[*i]) == true)
		*i += 1;
	if (input[*i] == '"' || input[*i] == '\'')
		*i += 1;
	printf("passed1\n");
	len = envvarlen(input + *i + 1, ' ');
	printf("passed2\n");
	ret = create_ambigu_node(len + 1);
	if (ret == NULL)
		return (nullerr("failed to malloc ambigu node"));
	printf("passed3\n");
	while (j <= len)
	{
		ret->arg[0][j] = input[*i];
		j++;
		*i += 1;
	}
	ret->arg[0][j] = '\0';
	printf("current string: %s, i before things: %d\n", ret->arg[0], *i);
	if (input[*i] == '"' || input[*i] == '\'')
		*i += 1;
	printf("i after thign: %d\n", *i);
	while (is_whitespace(input[*i]) == true)
		*i += 1;
	printf("i after morethign: %d\n", *i);
	return (ret);
}

action_t	*parse_file(char *input, int32_t *i, env_vars_t *envp)
{
	action_t	*node;

	node = NULL;
	if (check_str_end(input, *i, 2) != 2)
		return (nullerr("no string after redirect"));
	if (!(input[*i] == '<' && input[*i + 1] == '<') && ambigu_redirect(input, *i, envp) == true)
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
