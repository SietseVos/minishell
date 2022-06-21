/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_env_vars_list.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 21:49:43 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/21 21:49:45 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static env_vars_t	*new_env_node(char *envp)
{
	env_vars_t	*new;

	new = malloc(sizeof(env_vars_t));
	if (!new)
		return (NULL);
	new->str = ft_strdup(envp);
	if (!new->str)
	{
		free (new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

bool	create_env_vars_list(char **envp, env_vars_t **env_head)
{
	env_vars_t	*tmp;
	env_vars_t	*new;
	int32_t		i;

	i = 0;
	while (envp[i])
	{
		new = new_env_node(envp[i]);
		if (!new)
			return (free_env_list_return_false(*env_head));
		if (i == 0)
		{
			tmp = new;
			*env_head = tmp;
			i++;
			continue ;
		}
		else
			tmp->next = new;
		tmp = tmp->next;
		i++;
	}
	return (clean_env_vars_list(env_head));
}
