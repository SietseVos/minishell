#include <unistd.h>
#include <stdio.h>

void	testfunction2(unsigned int i, char *c)
{
	printf("char: %c, ", c[i]);
	i = 0;
	c = 0;
}