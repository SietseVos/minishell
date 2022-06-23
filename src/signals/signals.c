
#include "minishell.h"
#include <signal.h>
#include <termios.h>

static void	handle_ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("\0", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 1;
}

void	sig_c_outside_fork(int32_t sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("\0", 0);
	rl_on_new_line();
}

void	init_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
