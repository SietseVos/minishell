#include "minishell.h"

void	printenvp(env_vars_t *print)
{
	while (print != 0)
	{
		printf("%s\n", print ->str);
		print = print ->next;
	}
	printf("\n");
}

void	printchararr(char **toprint)
{
	int32_t	i;

	i = 0;
	printf("\033[1;34min Arguments:\033[0m\n");
	while (toprint[i] != NULL)
	{
		printf("-%s-\n", toprint[i]);
		i++;
	}
}

void	print_actions(action_t *inlst)
{
	while (inlst)
	{
		printf("\033[1;36m===== node =====\033[31m\n");
		if (inlst ->type == 0)
			printf("Type: Infile\n");
		else if (inlst ->type == 1)
			printf("Type: Outfile\n");
		else if (inlst ->type == 2)
			printf("Type: Append\n");
		else if (inlst ->type == 3)
			printf("Type: Heredoc\n");
		else if (inlst ->type == 4)
			printf("Type: Trunicate\n");
		else if (inlst ->type == 5)
			printf("Type: Pipe \n");
		else if (inlst ->type == 6)
			printf("Type: std out\n");
		else if (inlst ->type == 7)
			printf("Type: noinput\n");
		else if (inlst ->type == 8)
			printf("Type: inpipe\n");
		printchararr(inlst ->arg);
		inlst = inlst ->next;
	}
}
