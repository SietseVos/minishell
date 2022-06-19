
#include "minishell.h"

static bool	print_export(env_vars_t *env)
{
	char	**env_strings;
	int32_t	i;

	i = 0;
	env_strings = env_list_to_array(env);
	if (!env_strings)
		return (-1);
	bubble_sort_array(env_strings, env_list_size(env));
	if (add_quotes_after_equal(env_strings) == -1)
		return (-1);
	while (env_strings[i])
	{
		printf("declare -x %s\n", env_strings[i]);
		free(env_strings[i]);
		i++;
	}
	free(env_strings);
	return (0);
}

static int32_t	check_valid_input(char	*input)
{
	int32_t	i;

	i = 0;
	if ((input[0] >= '0' && input[0] <= '9') || input[0] == '=')
	{
		write_error_with_strings("bash: export: `", input, \
								"': not a valid identifier\n");
		return (-1);
	}
	while (input[i])
	{
		if (input[i] == '=')
			break ;
		else if (input[i] == '-')
		{
			write_error_with_strings("bash: export: `", input, \
									"': not a valid identifier\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

static int32_t	add_to_list(char *input, env_vars_t *env)
{
	char	*new_node;

	new_node = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!new_node)
		return (-1);
	ft_strlcpy(new_node, input, ft_strlen(input) + 1);
	if (add_env_node(env, new_node) == -1)
	{
		free(new_node);
		return (-1);
	}
	return (0);
}

static int32_t	replace_current_in_list(char *input, env_vars_t *env)
{
	env_vars_t	*to_replace;
	char		*variable;
	int32_t		i;

	i = 0;
	variable = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!variable)
		return (false);
	while (input[i] && input[i] != '=')
	{
		variable[i] = input[i];
		i++;
	}
	to_replace = get_variable_node(env, variable);
	while (input[i])
	{
		variable[i] = input[i];
		i++;
	}
	free(to_replace->str);
	to_replace->str = variable;
	set_env_node_hasvalue(to_replace);
	return (true);
}

int32_t	export(char **args, env_vars_t *env)
{
	int32_t	i;

	i = 0;
	if (!*args)
		return (print_export(env));
	while (args[i])
	{
		if (check_valid_input(args[i]) == -1 || \
			(args[i][0] && args[i][0] == '_' && \
			(args[i][1] == '=' || args[i][1] == '\0')))
		{
			i++;
			continue ;
		}
		else if (is_already_in_list(args[i], env))
		{
			if (replace_current_in_list(args[i], env) == -1)
				return (-1);
		}
		else
			if (add_to_list(args[i], env) == -1)
				return (-1);
		i++;
	}
	return (0);
}

// dont allow _= variable, should be shell maintained only and cant? be changed.
