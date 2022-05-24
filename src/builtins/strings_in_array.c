
#include "minishell.h"

int32_t	strings_in_array(char **str)
{
	int32_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
