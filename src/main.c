#include "minishell.h"

int32_t	main(int32_t argc, char **argv, char **envp)
{
	action_t	*actions;
	env_vars_t	*env;
	char		*input;

	g_exit_status = 0;
	env = NULL;
	actions = NULL;
	init_signals();
	using_history();
	create_env_vars_list(envp, &env);
	while (1)
	{
		free_action_list(&actions);
		input = readline("\033[1;31m😈 Minihell 😈 ▸\033[0m ");
		if (!input)
			exit(g_exit_status); // free env vars & history first
		else if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		input = lexer(input);
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
		if (heredoc(actions) == -1 || executer(&actions, &env) == -1)
			continue ;
		// print_actions(actions);
		// system("leaks minishell");
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

// bash-3.2$ exit 123 > out
// exit 
// 
// 

/* cat -e:
	argument > infile redirect > pipe
	 */
