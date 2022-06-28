#include "minishell.h"

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
