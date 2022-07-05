/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 14:22:08 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/05 14:46:01 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

/**
 * Signal handler to handle the SIGINT whilst typing in a readline loop.
 * 
 * 	@param sig Integer representing the signal that called this function.
 * 
 * @return - N/A -
*/
static void	ctrl_c_inside_loop(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("\0", 0);
	rl_on_new_line();
	rl_redisplay();
	g_info.exit_status = 1;
}

/**
 * Signal handler to handle the signals SIGINT and SIGQUIT during
 * the executer. It will set the exit status to 130 or 131.
 * 
 * @param sig Integer representing the signal that called this function.
 * 
 * @return - N/A -
*/
void	handle_sig_executer(int32_t sig)
{
	if (sig == SIGINT)
		g_info.exit_status = 130;
	else if (sig == SIGQUIT)
		g_info.exit_status = 131;
}

/**
 * Signal handler used for the heredoc.
 * it will send a signal the the proccess reading and
 * writing to the heredoc file using kill with the signak SIGTERM.
 * 
 * @param sig Integer representing the signal that called this function.
 * 
 * @return - N/A -
*/
void	heredoc_handler(int32_t sig)
{
	(void) sig;
	printf("\n");
	kill(g_info.heredoc_pid, SIGTERM);
	g_info.heredoc_breakout = true;
	g_info.exit_status = 130;
}

/**
 * Function to reset the SIGINT to the loop handler
 * and to ignore the SIGQUIT signal.
 * Also disables the signals from appearing in the terminal.
 * 
 * @param N/A
 * 
 * @return - N/A - 
*/
void	init_signals(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
	signal(SIGINT, ctrl_c_inside_loop);
	signal(SIGQUIT, SIG_IGN);
}
