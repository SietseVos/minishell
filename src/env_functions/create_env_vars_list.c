
#include "minishell.h"

static void	str_copy(char *take, char *place)
{
	int32_t i;
	int32_t	j;

	i = 0;
	j = 0;
	while (take[i])
	{
		if (i > 0 && take[i - 1] == '=')
			break ;
		place[j] = take[i];
		i++;
		j++;
	}
	place[j] = '"';
	j++;
	while (take[i])
	{
		place[j] = take[i];
		i++;
		j++;
	}
	place[j] = '"';
	place[j + 1] = '\0';
}

static env_vars_t *new_env_node(int32_t strlen)
{
	env_vars_t *new;

	new = malloc(sizeof(env_vars_t));
	if (!new)
		exit(404);
	new->str = malloc(strlen + 2 * sizeof(char));
	if (!new->str)
		exit(404);
	new->next = NULL;
	return (new);
}

void	create_env_vars_list(char **envp, env_vars_t **env_head)
{
	env_vars_t	*tmp;
	int32_t		strlen;
	int32_t		i;

	i = 0;
	while (envp[i])
	{
		strlen = ft_strlen(envp[i]);
		if (i == 0)
		{
			tmp = new_env_node(strlen + 1);
			*env_head = tmp;
		}
		else
		{
			tmp->next = new_env_node(strlen + 1);
			tmp = tmp->next;
		}
		str_copy(envp[i], tmp->str);
		i++;
	}
}
