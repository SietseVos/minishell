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
	char			*str;
	char			*prompt;
	HISTORY_STATE	history;

	prompt = "minishell: ";
	using_history();
	while (1)
	{
		str = readline(prompt);
		add_history(str);
		print_history();
		printf("%s\n", str);
		free(str);
	}
}
