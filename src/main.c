
#include "minishell.h"

int32_t	main(int32_t argc, char **argv, char **envp)
{
	// action_t	*actions;
	env_vars_t	*env;
	char		*input;

	g_exit_status = 0;
	init_signals();
	using_history();
	create_env_vars_list(envp, &env);
	int32_t test = 0;
	while (test < 5)
	{
		test++;
		input = readline("\033[1;33mMinihell >\033[0m ");
		if (input[0] != '\0')
			add_history(input);
		input = lexer(input);
		printf("lexer output: %s\n", input);
		// actions = parser(input, env);
		free(input);
		// execute(actions, env);
	}
	(void) argc;
	(void) argv;
	return (0);
}
