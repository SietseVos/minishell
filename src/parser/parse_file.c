#include "minishell.h"

void	skip_operator_space(char *input, int32_t *i)
{
	while (is_whitespace(input[*i]) == false)
		*i += 1;
	while (is_whitespace(input[*i]) == true)
		*i += 1;
}

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

action_t	*parse_file(char *input, int32_t *i, env_vars_t *envp)
{
	action_t	*node;

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
