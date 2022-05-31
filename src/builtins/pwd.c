
#include "minishell.h"

void	pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	g_exit_status = 0;
}
