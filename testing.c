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

typedef struct action_s
{
	int				input_fd;
	int				output_fd;
	char			*command;
	char			*argument;
	struct action_s *next;
}	action_t;

typedef struct root_s
{
	action_t	*action_head;
	env_vars_t	*env_head;
	char		*input;
}	root_t;

int		len_to_next_pipe(char *str, int i)
{
	int	quote_count;
	int	single_quote_count;

	single_quote_count = 0;
	quote_count = 0;
	while (str[i])
	{
		if (str[i] == '\"' && single_quote_count == 0)
			quote_count += 1;
		else if (str[i] == '\'' && quote_count == 0)
			single_quote_count += 1;
		else if (str[i] == '|' && single_quote_count + quote_count == 0)
			return (i);
		if (single_quote_count == 2)
			single_quote_count = 0;
		if (quote_count == 2)
			quote_count = 0;
		i++;
	}
	return (i);
}

int		pipe_sides(char *str, int i)
{
	int	quote_count;
	int	single_quote_count;
	int	pipe_sides;

	single_quote_count = 0;
	quote_count = 0;
	pipe_sides = 1;
	while (str[i])
	{
		if (str[i] == '\"' && single_quote_count == 0)
			quote_count += 1;
		else if (str[i] == '\'' && quote_count == 0)
			single_quote_count += 1;
		else if (str[i] == '|' && single_quote_count + quote_count == 0)
			pipe_sides += 1;
		if (single_quote_count == 2)
			single_quote_count = 0;
		if (quote_count == 2)
			quote_count = 0;
		i++;
	}
	return (pipe_sides);
}
// this string "|" contains | one pipe
char	**split_on_pipes(root_t *root)
{
	char	**full_commands;
	int		next_pipe;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	next_pipe = 0;
	int	sides = pipe_sides(root->input, i);
	full_commands = malloc((sides + 1) * sizeof(char *));
	full_commands[sides] = NULL;
	if (!full_commands)
		exit(404);
	while (root->input[i])
	{
		j = 0;
		next_pipe = len_to_next_pipe(root->input, i);
		full_commands[k] = malloc((next_pipe + 1) * sizeof(char));
		while (i < next_pipe)
		{
			full_commands[k][j] = root->input[i];
			i++;
			j++;
		}
		full_commands[k][j] = '\0';
		k++;
		if (root->input[i])
			i++;
	}
	return (full_commands);
}

void	parser(root_t *root)
{
	char	**split_input;
	split_input = split_on_pipes(root);
	for (int i = 0; split_input[i]; i++)
		printf("%s\n", split_input[i]);
}

action_t	*new_action_node(void)
{
	action_t	*new;

	new = malloc(sizeof(action_t) * 1);
	if (!new)
		exit(404);
	new->argument = NULL;
	new->command = NULL;
	new->input_fd = STDIN_FILENO;
	new->output_fd = STDOUT_FILENO;
	new->next = NULL;
	return (new);
}

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

char	**env_list_to_array(env_vars_t *env_list)
{
	env_vars_t	*list;
	char		**env_array;
	int			i;
	int			j;

	i = 0;
	j = 0;
	list = env_list;
	env_array = malloc(sizeof(char *) * (env_list_size(env_list) + 1));
	while (i < env_list_size(env_list))
	{
		env_array[i] = malloc(sizeof(char) * ft_strlen(list->str) + 1);
		str_copy(list->str, env_array[i]);
		i++;
		list = list->next;
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
	root_t	root;
	char	**env_array;
	char	*prompt;
	char	*pwd;
	int		i;

	i = 0;
	prompt = "minishell: ";
	using_history();
	init_env_vars_list(envp, &root.env_head);
	env_array = env_list_to_array(root.env_head);
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
		root.input = readline(prompt);
		prompt = "minishell: ";
		add_history(root.input);

		parser(&root);
		if (strcmp("clear", root.input) == 0)
		{
			rl_clear_history();
			prompt = "histoy cleared: ";
		}
		else if (strcmp("history", root.input) == 0)
		{
			print_history();
		}
		else if (strcmp("before", root.input) == 0)
		{
			printf("this is ");
			printf("before ");
		}
		else if (strncmp("check ", root.input, 6) == 0)
		{
			if (access(root.input + 6, F_OK) == 0)
				printf("%s exists!\n", root.input + 6);
			else
				printf("%s does not exist!\n", root.input + 6);
		}
		else if (strcmp("pwd", root.input) == 0)
		{
			pwd = getcwd(NULL, 0);
			printf("%s\n", pwd);
			free(pwd);
		}
		else if (strncmp("cd ", root.input, 3) == 0)
		{
			if (chdir(root.input + 3) != 0)
				printf("%s: No such file or directory\n", root.input + 3);
		}
		else if (strcmp("ls", root.input) == 0) // not working?
		{
			char *test[2] = {"-la", "."};
			execve("/bin/ls", test, env_array);
		}
		else if (strcmp("exit", root.input) == 0)
		{
			exit(0);
		}
		// printf("%s\n", str);
		free(root.input);
		i++;
	}
}

// wait, waitpid, waitid - wait for process to change state
// changed state is remused by signal, killed etc.
// wait3 and wait4 give more info.

