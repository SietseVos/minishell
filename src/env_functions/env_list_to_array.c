
#include "minishell.h"

static void	str_copy(char *take, char *place)
{
	int32_t i;

	i = 0;
	while (take[i])
	{
		place[i] = take[i];
		i++;
	}
	place[i] = '\0';
}

char	**free_array_till_index(char **array, int32_t index)
{
	int32_t	i;

	i = 0;
	while (i < index)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	if (array)
		free(array);
	return (NULL);
}

int32_t	env_list_size(env_vars_t *env_list)
{
	int32_t	i;

	i = 0;
	while (env_list)
	{
		env_list = env_list->next;
		i++;
	}
	return (i);
}

char	**env_list_to_array(env_vars_t *env_list)
{
	env_vars_t	*list;
	char		**env_array;
	int32_t		i;

	i = 0;
	list = env_list;
	env_array = malloc(sizeof(char *) * (env_list_size(env_list) + 1));
	if (!env_array)
		return (NULL);
	while (i < env_list_size(env_list))
	{
		env_array[i] = malloc(sizeof(char) * ft_strlen(list->str) + 1);
		if (!env_array[i])
			return (free_array_till_index(env_array, i));
		str_copy(list->str, env_array[i]);
		i++;
		list = list->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
