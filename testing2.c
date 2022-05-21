#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_split.h"

// void	print_history(void)
// {
// 	HISTORY_STATE *history = history_get_history_state();
// 	for (int i = 1; i < history->length; i++)
// 	{
// 		HIST_ENTRY	*current;
// 		current = history_get(i);
// 		printf("%s\n", current->line);
// 	}
// }



/* lexer: sorting input
	parser: tokenize input
	example:
		input lexer: < file cat -e| grep "some tex"t" |echo 'test' jklw> "outfile
		output lexer: < file cat -e | grep "some tex" t " | echo 'test' jklw > " outfile
		check for wrong syntax
		output parser: linked list
		process the infile and remove it from list
		*/

	// < Makefile cat > test > test2

int	main(void)
{
	char	**args;
	char	*str;
	char	*prompt;
	int		i;

	prompt = "minishell: ";
	// using_history();
	while (1)
	{
		str = readline(prompt);
		args = ft_split(str, ' ');
		i = 0;
		while (args[i])
		{
			printf("%s\n", args[i]);
			i++;
		}
		free(str);
		// printf("\e[0m\e[?25l\e[2J");
	}
}
