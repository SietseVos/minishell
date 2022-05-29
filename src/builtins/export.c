
#include "minishell.h"

void	print_export(env_vars_t *env)
{
	char	**env_strings;
	char	*tmp;
	int32_t	lst_size;
	int32_t	i;
	int32_t	j;

	printf("past lst size\n");
	lst_size = env_list_size(env);
	env_strings = env_list_to_array(env);
	i = 0;
	while (env_strings[i])
	{
		printf(" BEFORE declare - x %s\n", env_strings[i]);
		i++;
	}
	while (lst_size) // does not work
	{
		i = 0;
		while (env_strings[i] && env_strings[i + 1])
		{
			j = 0;
			while (env_strings[i][j] && env_strings[i + 1][j])
			{	
				if (env_strings[i][j] == '=')
					break ;
				else
				{
					// printf("swapping strings %s and %s\n", env_strings[i], env_strings[i + 1]);
					tmp = env_strings[i];
					env_strings[i] = env_strings[i + 1];
					env_strings[i + 1] = tmp;
					break ;
				}
				if (env_strings[i][j] < env_strings[i + 1][j])
				{
					// printf("swapping strings %s and %s\n", env_strings[i], env_strings[i + 1]);
					tmp = env_strings[i];
					env_strings[i] = env_strings[i + 1];
					env_strings[i + 1] = tmp;
					break ;
				}
				j++;
			}
			i++;
		}
		lst_size--;
	}
	i = 0;
	// (put quotes around variable!!)
	while (env_strings[i])
	{
		printf("declare - x %s\n", env_strings[i]);
		i++;
	}
}

void	export(char **args, env_vars_t *env)
{
	int32_t	i;

	i = 0;
	printf("entering export\n");
	if (!*args)
		print_export(env);
	// else
	// {
	// 	while (args[i])
	// 	{
	//		// if invalid input
	// 		// if has =
	// 		// if has value
	// 		// if no =
	// 		i++;
	// 	}
	// }
}
