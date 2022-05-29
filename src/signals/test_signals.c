
#include "minishell.h"

int	main(void)
{
	char		prompt[] = "signals.c = ";
	char		*input;
	uint32_t	i = 0;

	init_signals();
	using_history();
	while (i < 5)
	{
		input = readline(prompt);
		if (input && input[0] != '\0')
			add_history(input);
		free(input);
		i++;
	}
}

// gcc signals.c test_signals.c -I ../../include/ -I ../../src/libft ../../src/libft/libft.a -L/Users/rvan-mee/homebrew/opt/readline/lib -I /Users/rvan-mee/homebrew/opt/readline/include -lreadline -fsanitize=address -g
