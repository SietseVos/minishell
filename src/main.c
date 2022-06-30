/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 16:56:19 by svos          #+#    #+#                 */
/*   Updated: 2022/06/30 13:40:39 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_vars_main(char **envp, t_env_vars **env, int argc, char **argv)
{
	(void) argc;
	(void) argv;
	g_info.exit_status = 0;
	using_history();
	return (create_env_vars_list(envp, env));
}

static char	*get_input(char *input)
{
	const char	prompt[] = "\001\033[1;31m\002Minihell>\001\033[0m\002 ";

	while (1)
	{
		if (input)
			free(input);
		input = readline(prompt);
		if (!input)
		{
			write(STDERR_FILENO, "exit\n", 6); // needs to be on the same line as readline.
			exit(g_info.exit_status);
		}
		else if (input[0] != '\0')
		{
			add_history(input);
			return (lexer(input));
		}
	}
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_heredoc	*hdoc_files;
	t_action	*actions;
	char		*input;
	t_env_vars	*env;

	input = NULL;
	if (init_vars_main(envp, &env, argc, argv) == false)
		return (1);
	while (1)
	{
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

		// system("leaks minishell");
		// printf("Current exit status: %d\n", g_info.exit_status);




// export bla="s -l"

// l$bla

// segfault:
// export a=5=5

// misschien doen?
// export a+=10

// jullie path wordt niet van voren naar achteren afgegaan

// globals zijn niet goed verantwoord. struct is ook erg stiekem