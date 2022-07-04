
#include "minishell.h"

bool	check_for_append_export(char *input)
{
	int32_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '+')
			return (true);
		else if (input[i] == '=')
			return (false);
		i++;
	}
	return (false);
}

bool	add_to_existing_var(t_env_vars *env, char *to_add)
{
    t_env_vars 	*node;
	size_t		size;
	char		*str;
	int32_t		i;
    
	node = get_variable_node(env, to_add);
	while (to_add[i] && to_add[i] != '=')
		i++;
	if (to_add[i] == '=' && node->has_value)
		i++;
	size = ft_strlen(node->str) + ft_strlen(&to_add[i]) + NULL_TERM;
	str = ft_calloc(size, sizeof(char));
	if (!str)
		return (false);
	ft_strlcat(str, node->str, size);
	ft_strlcat(str, &to_add[i], size);
	free(node->str);
	node->str = str;
	set_env_node_hasvalue(node);
	return (true);
}
