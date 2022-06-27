#include "minishell.h"

static bool	init_vars_main(char **envp, env_vars_t **env, int argc, char **argv)
{
	(void)	argc;
	(void)	argv;
	g_exit_status = 0;
	using_history();
	return (create_env_vars_list(envp, env));
}

static char	*readline_func(char *input)
{
	while (1)
	{
		if (input)
			free(input);
		input = readline("\033[1;31m😈 Minihell 😈 ▸\033[0m ");
		if (!input)
			exit(g_exit_status); // free env vars & history first?
		else if (input[0] != '\0')
		{
			add_history(input);
			return (input);
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
		// printf("Current exit status: %d\n", g_exit_status);
		// init_signals();
		remove_heredoc_files(&hdoc_files);
		free_action_list(&actions);
		input = readline_func(input);
		input = lexer(input);
		if (!input)
			continue ;
		actions = parser(input, env);
		if (!actions)
			continue ;
		// if (heredoc(actions, &hdoc_files) == -1 || executer(&actions, &env) == -1)
		// 	continue ;
		print_actions(actions);
		system("leaks minishell");
		// printf("global exit status: %d\n", g_exit_status);
	}
	clear_history(); // ?? can we use this?? rl_clear_history?
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
