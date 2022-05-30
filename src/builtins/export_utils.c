
#include "minishell.h"

static void	swap_strings(char **strings, int32_t str1, int32_t str2)
{
	char	*tmp;

	tmp = strings[str1];
	strings[str1] = strings[str2];
	strings[str2] = tmp;
}

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

static void	set_quotes_in_string(char **string, int32_t str, char *tmp, bool *past_equals)
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

void	add_quotes_after_equal(char **strings)
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
			exit(404);
		set_quotes_in_string(strings, i, tmp, &past_equals);
		i++;
	}
}

bool	is_already_in_list(char	*input, env_vars_t *env)
{
	int32_t	i;

	i = 0;
	while (input[i] && input[i] != '=')
		i++;
	while (env)
	{
		if (ft_strncmp(input, env->str, i) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}
