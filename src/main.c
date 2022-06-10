#include "minishell.h"

int32_t	main(int32_t argc, char **argv, char **envp)
{
	action_t	*actions;
	env_vars_t	*env;
	char		*input;
	// char		input1[] = "exit";

	g_exit_status = 0;
	init_signals();
	using_history();
	create_env_vars_list(envp, &env);
	int32_t test = 0;
	while (test < 50)
	{
		test++;
		input = readline("\033[1;31mMinihell>\033[0m ");
		if (!input || (input && input[0] == '\0'))
			continue ;
		add_history(input);
		input = lexer(input);
		// printf("lexer output:\n-%s-\n", input);
		if (!input)
			continue ;
		actions = parser(input, env);
		if (!actions)
		{
			free(input);
			continue ;
		}
		free(input);
		print_actions(actions);
		if (ft_strncmp(actions ->arg[0], "exit", 4) == 0)
			return (0);
		// executer_setup(actions, env);
		// execute(actions, env);
	}
	clear_history(); // ?? can we use this?? rl_clear_history?
	(void)	argc;
	(void)	argv;
	return (0);
}

// weird bash cases
// < Makefile cat -e | cat -e > out.ofdsuiod | ls | cat -e > out.two
// < Makefile cat -e | cat -e | cat -e | cat -e < testing.c | cat -e  > out.two
// export TEST=test | echo $TEST
// ls | cat -e > out.two out.txt
// ls | cat -e < Makefile out.txt testing.c
// cat -e < Makefile > out.txt | cat -e < testing.c > out.two

/* cat -e:
	argument > infile redirect > pipe
	 */
