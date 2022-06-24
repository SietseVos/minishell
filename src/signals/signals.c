
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

void	handle_sig_executer(int32_t sig)
{
	if (sig == SIGINT)
		g_exit_status = 130;
	else if (sig == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit: 3\n", 9);
		g_exit_status = 131;
	}
}

void	sig_c_outside_fork(int32_t sig)
{
	(void)sig;
	g_exit_status = 130;
	printf("\n");
	rl_replace_line("\0", 0);
	rl_on_new_line();
}

void	init_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
