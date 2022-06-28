#include "minishell.h"

static bool	init_vars_main(char **envp, env_vars_t **env, int argc, char **argv)
{
	(void)	argc;
	(void)	argv;
	g_info.exit_status = 0;
	using_history();
	return (create_env_vars_list(envp, env));
}

static char	*get_input(char *input)
{
	const char prompt[] = "\001\033[1;31m\002Minihell>\001\033[0m\002 ";

	while (1)
	{
		if (input)
			free(input);
		input = readline(prompt);
		if (!input)
			exit(g_info.exit_status);
		else if (input[0] != '\0')
		{
			add_history(input);
			return (lexer(input));
		}
	}
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	heredoc_t	*hdoc_files;
	action_t	*actions;
	char		*input;
	env_vars_t	*env;

	env = NULL;
	input = NULL;
	actions = NULL;
	hdoc_files = NULL;
	if (init_vars_main(envp, &env, argc, argv) == false)
		return (1);
	while (1)
	{
		// printf("Current exit status: %d\n", g_info.exit_status);
		init_signals();
		remove_heredoc_files(&hdoc_files);
		free_action_list(&actions);
		input = get_input(input);
		if (!input)
			continue ;
		actions = parser(input, env);
		if (!actions)
			continue ;
		if (heredoc(actions, &hdoc_files, env) == -1)
			continue ;
		executer(&actions, &env);
		// system("leaks minishell");
	}
	return (0);
}
