
#include "minishell.h"
#include <signal.h>
#include <termios.h>

static void	ctrl_c_inside_loop(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("\0", 0);
	rl_on_new_line();
	rl_redisplay();
	g_info.exit_status = 1; // is 130 on linux
}

void	handle_sig_executer(int32_t sig)
{
	if (sig == SIGINT)
		g_info.exit_status = 130;
	else if (sig == SIGQUIT)
		g_info.exit_status = 131;
}

void	heredoc_handler(int32_t sig)
{
	(void)	sig;
	printf("\n");
	kill(g_info.heredoc_pid, SIGTERM);
	g_info.heredoc_breakout = true;
	g_info.exit_status = 130;
}

void	init_signals(void)
{
	struct termios t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
	signal(SIGINT, ctrl_c_inside_loop);
	signal(SIGQUIT, SIG_IGN);
}
