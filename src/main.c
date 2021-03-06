/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 16:56:19 by svos          #+#    #+#                 */
/*   Updated: 2022/07/06 12:47:37 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_vars_main(char **envp, t_env_vars **env, int argc, char **argv)
{
	(void) argc;
	(void) argv;
	g_info.exit_status = 0;
	printf("\033[1;31m   , ,, ,                     \n\
   | || |    ,/  _____  \\.             \n\
   \\_||_/    ||_/     \\_||             \n\
     ||       \\_| . . |_/              \n\
     ||         |  L  |                \n\
    ,||         |`==='|                \n\
    |>|      ___`>  -<'___             \n\
    |>|\\    /             \\            \n\
    \\>| \\  /  ,    .    .  |           \n\
     ||  \\/  /| .  |  . |  |           \n\
     ||\\  ` / | ___|___ |  |     (     \n\
  (( || `--\'  | _______ |  |     ))  ( \n\
(  )\\|| (  )\\ | - --- - | -| (  ( \\  ))\n\
(\\/  || ))/ ( | -- - -- |  | )) )  \\(( \n\
 ( ()||((( ())|         |  |( (( () )\n\033[0m");
	using_history();
	return (create_env_vars_list(envp, env));
}

static char	*get_input(char *input, t_env_vars *env)
{
	const char	prompt[] = "\001\033[1;31m\002Minihell>\001\033[0m\002 ";

	while (1)
	{
		if (input)
			free(input);
		input = readline(prompt);
		if (!input)
		{
			printf("\033[1A\033[1;31mMinihell>\033[0m exit\n");
			exit(g_info.exit_status);
		}
		else if (input[0] != '\0')
		{
			add_history(input);
			return (expander(lexer(input), env));
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
	hdoc_files = NULL;
	if (init_vars_main(envp, &env, argc, argv) == false)
		return (1);
	while (1)
	{
		init_signals();
		remove_heredoc_files(&hdoc_files);
		free_action_list(&actions);
		input = get_input(input, env);
		if (!input)
			continue ;
		actions = parser(input, env);
		if (!actions)
			continue ;
		if (heredoc(actions, &hdoc_files, env) == -1)
			continue ;
		executer(&actions, &env);
	}
	return (0);
}
