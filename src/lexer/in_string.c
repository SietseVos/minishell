
#include "minishell.h"

static int32_t	reset_and_return(int32_t *double_quote, int32_t *single_quote, bool return_v)
{
	if (double_quote)
		*double_quote = 0;
	if (single_quote)
		*single_quote = 0;
	return (return_v);
}

bool in_string(char c, bool reset)
{
	static int32_t	double_quote = 0;
	static int32_t	single_quote = 0;

	if (reset)
		return(reset_and_return(&double_quote, &single_quote, false));
	if (c != '\'' && c != '"' && !double_quote && !single_quote)
		return (false);
	if (c == '\'' && !double_quote)
	{
		single_quote++;
		if (single_quote == 2)
			return (reset_and_return(NULL, &single_quote, true));
		return (false);
	}
	else if (c == '"' && !single_quote)
	{
		double_quote++;
		if (double_quote == 2)
			return (reset_and_return(&double_quote, NULL, true));
		return (false);
	}
	return (true);
}

void	skip_string(char *str, int32_t *i)
{
	if (in_string(str[*i], false))
		*i += 1;
	while (str[*i] && in_string(str[*i], false))
		*i += 1;
	in_string(str[*i], true);
}
