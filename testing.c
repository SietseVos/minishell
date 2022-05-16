#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*str;
	char	*prompt;

	prompt = "minishell: ";
	while (1)
	{
		str = readline(prompt);
		printf("%s\n", str);
		free(str);
	}
}