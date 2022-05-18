#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct env_vars_s
{
	char				*str;
	struct env_vars_s	*next;
}	env_vars_t;

int	ft_strlen(char	*str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

env_vars_t *new_env_node(int strlen)
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

void	str_copy(char *take, char *place)
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

void	init_env_vars_list(char **envp, env_vars_t **env_head)
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

int	env_list_size(env_vars_t *env_list)
{
	int	i;

	i = 0;
	while (env_list)
	{
		env_list = env_list->next;
		i++;
	}
	return (i);
}

char	**env_list_to_array(env_vars_t **env_head)
{
	env_vars_t	*tmp;
	char		**env_array;
	int			i;
	int			j;

	i = 0;
	j = 0;
	tmp = *env_head;
	env_array = malloc(sizeof(char *) * (env_list_size(*env_head) + 1));
	while (i < env_list_size(*env_head))
	{
		env_array[i] = malloc(sizeof(char) * ft_strlen(tmp->str) + 1);
		str_copy(tmp->str, env_array[i]);
		i++;
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	print_history(void)
{
	HISTORY_STATE *history = history_get_history_state();
	for (int i = 1; i < history->length; i++)
	{
		HIST_ENTRY	*current;
		current = history_get(i);
		printf("%s\n", current->line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	env_vars_t	**env_head;
	char		**env_array;
	char		*str;
	char		*prompt;
	char		*pwd;
	int			i;

	i = 0;
	prompt = "minishell: ";
	using_history();
	init_env_vars_list(envp, env_head);
	env_array = env_list_to_array(env_head);
	// env_vars_t *tmp = *env_head;
	// while (tmp)
	// {
	// 	if (tmp->str)
	// 		printf("%s\n", tmp->str);
	// 	tmp = tmp->next;
	// }
	// for (int i = 0; env_array[i]; i++)
	// 	printf("%s\n", env_array[i]);
	while (1)
	{
		str = readline(prompt);
		prompt = "minishell: ";
		add_history(str);

		if (strcmp("clear", str) == 0)
		{
			rl_clear_history();
			prompt = "histoy cleared: ";
		}
		else if (strcmp("history", str) == 0)
		{
			print_history();
		}
		else if (strcmp("before", str) == 0)
		{
			printf("this is ");
			printf("before ");
		}
		else if (strncmp("check ", str, 6) == 0)
		{
			if (access(str + 6, F_OK) == 0)
				printf("%s exists!\n", str + 6);
			else
				printf("%s does not exist!\n", str + 6);
		}
		else if (strcmp("pwd", str) == 0)
		{
			pwd = getcwd(NULL, 0);
			printf("%s\n", pwd);
			free(pwd);
		}
		else if (strncmp("cd ", str, 3) == 0)
		{
			if (chdir(str + 3) != 0)
				printf("%s: No such file or directory\n", str + 3);
		}
		else if (strcmp("ls", str) == 0) // not working?
		{
			char *test[2] = {"-la", "."};
			execve("/bin/ls", test, env_array);
		}
		else if (strcmp("exit", str) == 0)
		{
			exit(0);
		}
		// printf("%s\n", str);
		free(str);
		i++;
	}
}

// wait, waitpid, waitid - wait for process to change state
// changed state is remused by signal, killed etc.
// wait3 and wait4 give more info.

