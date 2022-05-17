#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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

int	main(void)
{
	char	*str;
	char	*prompt;
	char	*pwd;
	int		i;

	i = 0;
	prompt = "minishell: ";
	using_history();
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
		// printf("%s\n", str);
		free(str);
		i++;
	}
}

// wait, waitpid, waitid - wait for process to change state
// changed state is remused by signal, killed etc.
// wait3 and wait4 give more info.

