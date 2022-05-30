
#include "minishell.h"

static void	print_export(env_vars_t *env)
{
	char	**env_strings;
	int32_t	i;

	i = 0;
	env_strings = env_list_to_array(env);
	bubble_sort_array(env_strings, env_list_size(env));
	add_quotes_after_equal(env_strings);
	while (env_strings[i])
	{
		printf("declare - x %s\n", env_strings[i]);
		free(env_strings[i]);
		i++;
	}
	free(env_strings);
}

static bool	check_valid_input(char	*input)
{
	int32_t	i;

	i = 0;
	if ((input[0] >= '0' && input[0] <= '9') || input[0] == '=')
		return (true);
	while (input[i])
	{
		if (input[i] == '=')
			break ;
		else if (input[i] == '-')
			return (true);
		i++;
	}
	return (false);
}

static void	add_to_list(char *input, env_vars_t *env)
{
	char	*new_node;

	new_node = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!new_node)
		exit(404);
	ft_strlcpy(new_node, input, ft_strlen(input) + 1);
	add_env_node(env, new_node);
}

static void	replace_current_in_list(char *input, env_vars_t *env)
{
	env_vars_t	*to_replace;
	char		*variable;
	int32_t		i;

	i = 0;
	variable = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!variable)
		exit(404);
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
}

void	export(char **args, env_vars_t *env)
{
	int32_t	i;

	i = 0;
	if (!*args)
		print_export(env);
	else
	{
		while (args[i])
		{
			if (check_valid_input(args[i]))
				printf("bash: export: `%s': not a valid identifier\n", args[i]);
			else if (args[i][0] && args[i][0] == '_' && args[i][1] && args[i][1] == '=') // checks for shell variable, can't be edited by the user
				continue ;
			else if (is_already_in_list(args[i], env))
				replace_current_in_list(args[i], env);
			else
				add_to_list(args[i], env);
			i++;
		}
	}
}

// dont allow _= variable, should be shell maintained only and cant? be changed.
