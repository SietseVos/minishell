
#include "minishell.h"

int	strings_in_array(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
