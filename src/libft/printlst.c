#include "libft.h"
#include <stdio.h>

void	printlst(t_list *print)
{
	while (print != 0)
	{
		printf("%s|", print ->content);
		print = print ->next;
	}
}
