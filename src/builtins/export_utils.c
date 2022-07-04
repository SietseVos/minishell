/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:21:44 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 17:50:04 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to swap the pointers of 2 strings inside an array.
 * 
 * @param strings Double char array countaining broth strings.
 *
 * @param str1 Position of the first string inside the array. 
 * 
 * @param str2 Position of the second string inside the array.
 * 
 * @return N/A
*/
static void	swap_strings(char **strings, int32_t str1, int32_t str2)
{
	char	*tmp;

	tmp = strings[str1];
	strings[str1] = strings[str2];
	strings[str2] = tmp;
}

/**
 * Function to bubble sort a double char array
 * based on ascii value of the characters inside.
 * 
 * @param env_strings Double char array containing
 * all the strings to be sorted.
 * 
 * @param lst_size Amount of strings inside the array.
 * 
 * @return N/A
*/
void	bubble_sort_array(char **env_strings, int32_t lst_size)
{
	int32_t	i;
	int32_t	j;

	while (lst_size-- >= 0)
	{
		i = 0;
		while (env_strings[i] && env_strings[i + 1])
		{
			j = 0;
			while (env_strings[i][j] && env_strings[i + 1][j])
			{	
				if ((env_strings[i][j] == '=' || env_strings[i + 1][j] == '=')
					|| (env_strings[i][j] < env_strings[i + 1][j]))
					break ;
				else if (env_strings[i][j] > env_strings[i + 1][j])
				{
					swap_strings(env_strings, i, i + 1);
					break ;
				}
				j++;
			}
			i++;
		}
	}
}

/**
 * Function to set quotes before and after the given string.
 * Wont set quotes if the string does not contain '='.
 * 
 * @param string Double char array containing all strings.
 * 
 * @param str Index of the original string. 
 * 
 * @param tmp Pointer to the new string where the quotes
 * have to be included.
 * 
 * @param past_equals Pointer to a boolian keepeing track if
 * an equals sign has been passed.
 *
 * @return N/A
*/
static void	set_quotes_in_string(char **string, int32_t str, \
								char *tmp, bool *past_equals)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	j = 0;
	while (string[str][i])
	{
		tmp[j] = string[str][i];
		if (string[str][i] == '=' && !*past_equals)
		{
			*past_equals = true;
			tmp[++j] = '"';
		}
		i++;
		j++;
	}
	if (*past_equals)
		tmp[j] = '"';
	free(string[str]);
	string[str] = tmp;
}

/**
 * Function to add quotes after the equals sign.
 * 
 * @param strings Double char array containing all
 * strings that have to be changed.
 * 
 * @return - [0] success - [-1] malloc fail -
*/
int32_t	add_quotes_after_equal(char **strings)
{
	int32_t	i;
	bool	past_equals;
	char	*tmp;

	i = 0;
	while (strings[i])
	{
		past_equals = false;
		tmp = ft_calloc(strlen(strings[i]) + 3, sizeof(char));
		if (!tmp)
			return (-1);
		set_quotes_in_string(strings, i, tmp, &past_equals);
		i++;
	}
	return (0);
}

/**
 * Function to search for a given string inside the
 * environment variables.
 * 
 * @param input Pointer to the string to search for.
 * 
 * @param env pointer to the env list containing all nodes.
 * 
 * @return - [true] If found inside list - [false] not inside list -
*/
bool	is_already_in_list(char	*input, t_env_vars *env)
{
	int32_t	i;

	i = 0;
	while (input[i] && input[i] != '=' && input[i] != '+')
		i++;
	while (env)
	{
		if (ft_strncmp(input, env->str, i) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}
