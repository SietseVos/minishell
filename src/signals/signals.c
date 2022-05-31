
#include "minishell.h"
#include <signal.h>

void	handle_ctrl_slash(int sig)
{
	(void)sig;
}

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
	// handle ctrl-D?
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_slash);
}

// ctrl-D exits shell unless there is something in the readline buffer	----- Not a signal, ascii (4), EOF 
// ctrl-C display a newline and empty the readline buffer				----- SIGINT
// ctrl-\ does nothing													----- SIGQUIT
