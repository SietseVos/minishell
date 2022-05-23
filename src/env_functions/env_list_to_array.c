
#include "minishell.h"

static void	str_copy(char *take, char *place)
{
	int i;

	i = 0;
	while (take[i])
	{
		place[i] = take[i];
		i++;
	}
	place[i] = '\0';
}

static int	env_list_size(env_vars_t *env_list)
{
	int	i;

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
	int			i;
	int			j;

	i = 0;
	j = 0;
	list = env_list;
	env_array = malloc(sizeof(char *) * (env_list_size(env_list) + 1));
	while (i < env_list_size(env_list))
	{
		env_array[i] = malloc(sizeof(char) * ft_strlen(list->str) + 1);
		str_copy(list->str, env_array[i]);
		i++;
		list = list->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
