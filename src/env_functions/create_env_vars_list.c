
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

static void	increment_shell_level(env_vars_t *list)
{
	int32_t	level;
	char	*new_str;
	char	*new_num;

	while (list)
	{
		if (ft_strncmp("SHLVL=", list->str, 6) == 0)
		{
			level = ft_atoi(&list->str[6]);
			level++;
			new_num = ft_itoa(level);
			if (!new_num)
				exit(404);
			new_str = malloc(sizeof(char) * (ft_strlen(new_num) + 7));
			if (!new_str)
				exit(404);
			str_copy("SHLVL=", new_str);
			ft_strlcat(new_str, new_num, ft_strlen(new_num) + 7);
			free(new_num);
			free(list->str);
			list->str = new_str;
			break ;
		}
		list = list->next;
	}
}

static void	remove_oldpwd_from_list(env_vars_t **list)
{
	env_vars_t	*pre;
	env_vars_t	*tmp;
	env_vars_t	*next;
	int32_t		i;

	tmp = *list;
	while (tmp)
	{
		if (ft_strncmp("OLDPWD=", tmp->str, 7) == 0)
		{
			next = tmp->next;
			free(tmp->str);
			free(tmp);
			if (i == 0)
				*list = next;
			else
				pre->next = next;
			break ;
		}
		i++;
		pre = tmp;
		tmp = tmp->next;
	}
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
	remove_oldpwd_from_list(env_head);		// remove _= too (shell variable)
	increment_shell_level(*env_head);		// maybe put this inside of main
}
