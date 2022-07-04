
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
	g_info.exit_status = 130;
}

void	handle_sig_executer(int32_t sig)
{
	if (sig == SIGINT)
		g_info.exit_status = 130;
	else if (sig == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit: 3\n", 9);
		g_info.exit_status = 131;
	}
}

void	sig_c_outside_fork(int32_t sig)
{
	(void)sig;
	g_info.exit_status = 130;
	printf("\n");
	rl_replace_line("\0", 0);
	rl_on_new_line();
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
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
