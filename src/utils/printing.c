/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 14:13:14 by svos          #+#    #+#                 */
/*   Updated: 2022/07/05 14:13:15 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printenvp(t_env_vars *print)
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
	if (toprint == NULL)
		return ;
	while (toprint[i] != NULL)
	{
		printf("-%s-\n", toprint[i]);
		i++;
	}
}

void	print_actions(t_action *inlst)
{
	if (!inlst)
		printf("\033[1;32mList is empty!\033[31m\n");
	while (inlst)
	{
		printf("\033[1;36m===== node =====\033[31m\n");
		if (inlst ->type == INFILE)
			printf("Type: Infile\n");
		else if (inlst ->type == AMBIGU)
			printf("Type: Ambiguous\n");
		else if (inlst ->type == APPEND)
			printf("Type: Append\n");
		else if (inlst ->type == TRUNC)
			printf("Type: Trunicate\n");
		else if (inlst ->type == PIPE)
			printf("Type: Pipe \n");
		else if (inlst ->type == TOSTDOUT)
			printf("Type: std out\n");
		else if (inlst ->type == HDOCSPACE)
			printf("Type: Heredoc space\n");
		else if (inlst ->type == HDOCQUOTE)
			printf("Type: Heredoc quote\n");
		printchararr(inlst ->arg);
		inlst = inlst ->next;
	}
}
