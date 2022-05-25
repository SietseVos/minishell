
#include "minishell.h"

void	pwd(char **argument)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	g_exit_status = 0;
}