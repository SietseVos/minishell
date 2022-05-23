
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

static env_vars_t *new_env_node(int strlen)
{
	env_vars_t *new;

	new = malloc(sizeof(env_vars_t));
	if (!new)
		exit(404);
	new->str = malloc(strlen * sizeof(char));
	if (!new->str)
		exit(404);
	new->next = NULL;
	return (new);
}

void	create_env_vars_list(char **envp, env_vars_t **env_head)
{
	env_vars_t	*tmp;
	int			strlen;
	int			i;

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
