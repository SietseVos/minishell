
#include "minishell.h"
#include <signal.h>

void	handle_ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("\0", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	init_signals(void)
{
	// signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
