
#include "minishell.h"

bool in_string(char c, bool reset)
{
	static int	double_quote = 0;
	static int	single_quote = 0;

	if (reset)
	{
		double_quote = 0;
		single_quote = 0;
		return (false);
	}
	if (c != '\'' && c != '"' && !double_quote && !single_quote)
		return (false);
	if (c == '\'' && !double_quote)
		single_quote++;
	else if (c == '"' && !single_quote)
		double_quote++;
	if (double_quote == 2)
	{
		double_quote = 0;
		return (true);
	}
	else if (single_quote == 2)
	{
		single_quote = 0;
		return (true);
	}
	return (true);
}
