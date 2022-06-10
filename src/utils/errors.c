#include "minishell.h"

void	*nullerr(char *errmsg)
{
	printf("%s :(\n",errmsg);
	return (NULL);
}

bool	boolerr(char *errmsg)
{
	printf("%s :(\n",errmsg);
	return (false);
}
