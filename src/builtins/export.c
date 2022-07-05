/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:21:32 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/05 13:07:05 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to print the entire environment variable list,
 * sorted by ascii value.
 * 
 * @param env Pointer to the environment variable list.
 * 
 * @return - [0] Success - [-1] Malloc failed -
*/
static bool	print_export(t_env_vars *env)
{
	char	**env_strings;
	int32_t	i;

	i = 0;
	env_strings = env_list_to_array(env);
	if (!env_strings)
		return (-1);
	bubble_sort_array(env_strings, env_list_size(env));
	if (add_quotes_after_equal(env_strings) == -1)
	{
		free_double_array(env_strings);
		return (-1);
	}
	while (env_strings[i])
	{
		printf("declare -x %s\n", env_strings[i]);
		free(env_strings[i]);
		i++;
	}
	free(env_strings);
	return (0);
}

/**
 * Function to check if the input is correct.
 * 
 * @param inp Pointer to the string that needs to be checked.
 * 
 * @return - [0] Input correct - [-1] Input incorrect -
*/
static int32_t	check_valid_input(char	*inp)
{
	int32_t	i;

	i = 0;
	if (inp[0] == '\0' || (inp[0] >= '0' && inp[0] <= '9')
		|| inp[0] == '=' || inp[0] == '+')
	{
		write_error_with_strings(EXPORT_ERROR, inp, IDENT_ERROR);
		if (g_info.exit_status == 0)
			g_info.exit_status = 1;
		return (-1);
	}
	while (inp[i])
	{
		if (inp[i] == '=' || (inp[i] == '+' && inp[i + 1] == '='))
			break ;
		else if (!(ft_isalnum(inp[i]) || inp[i] == '_'))
		{
			write_error_with_strings(EXPORT_ERROR, inp, IDENT_ERROR);
			if (g_info.exit_status == 0)
				g_info.exit_status = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}

/**
 * Function to create a new env node with the given value
 * inside of it.
 * 
 * @param input Pointer to the string that needs to be set inside 
 * the new environment node.
 * 
 * @param env Pointer to the head of the environment variable list.
 * 
 * @return - [0] Success - [-1] Malloc failed -
*/
static int32_t	add_to_list(char *input, t_env_vars **env)
{
	char	*new_str;
	bool	past_equals;
	int32_t	i;

	i = 0;
	past_equals = false;
	new_str = ft_calloc(ft_strlen(input) + NULL_TERM, sizeof(char));
	if (!new_str)
		return (-1);
	while (*input)
	{	
		if (*input == '+' && past_equals == false)
			input++;
		if (*input == '=')
			past_equals = true;
		new_str[i] = *input;
		input++;
		i++;
	}
	if (add_env_node(env, new_str) == -1)
	{
		free(new_str);
		return (-1);
	}
	return (0);
}

/**
 * Function to replace the current value inside the node that
 * contains the same variable name as the given input.
 * 
 * @param input Pointer to the string containing variable and
 * the new value that has to be set.
 * 
 * @param env Pointer to the environment variable list.
 * 
 * @return - [true] Success - [false] Malloc failed -
*/
static int32_t	replace_current_in_list(char *input, t_env_vars *env)
{
	t_env_vars	*to_replace;
	char		*variable;
	int32_t		i;

	i = 0;
	if (check_for_append_export(input))
		return (add_to_existing_var(env, input));
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

/**
 * Builtin function to replicate the behaviour of Bash's export
 * without and flags. 
 * 
 * @param args Double char array containing all the agruments
 * export has to work with.
 * 
 * @param env Pointer to the head of the environment variable list.
 * 
 * @return - [0] Success - [-1] Malloc failed -
*/
int32_t	export(char **args, t_env_vars **env)
{
	int32_t	i;

	i = 0;
	g_info.exit_status = 0;
	if (!*args)
		return (print_export(*env));
	while (args[i])
	{
		if (check_valid_input(args[i]) == -1 || (args[i][0] && \
			args[i][0] == '_' && (args[i][1] == '=' || args[i][1] == '\0')))
		{
			i++;
			continue ;
		}
		else if (is_already_in_list(args[i], *env))
		{
			if (replace_current_in_list(args[i], *env) == -1)
				return (-1);
		}
		else if (add_to_list(args[i], env) == -1)
			return (-1);
		i++;
	}
	return (0);
}
