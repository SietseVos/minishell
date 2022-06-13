#include "minishell.h"

void	free_double_array(char **array)
{
	int32_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
}
