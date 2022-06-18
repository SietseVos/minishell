#include "minishell.h"

action_t	*parse_pipe(char *input, int32_t *i)
{
	action_t	*ret;

	ret = malloc(sizeof(action_t));
	if (ret == NULL)
		return (nullerr("failed to malloc pipe node"));
	ret->type = PIPE;
	ret->arg = NULL;
	*i += 1;
	while (input[*i] != '\0' && is_whitespace(input[*i]))
		*i += 1;
	// printf("entered pipe function\n");
	return (ret);
}