
#include "minishell.h"

void	pwd(char **argument)
{
	char *pwd;
	if (strings_in_array(argument))
	{
		printf("pwd: too many arguments\n");
		// set exit value 1
	}
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	// set exit value 0
}