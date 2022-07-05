/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 20:03:45 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/05 14:08:47 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/wait.h>

/**
 * Function to close the given fd and free the given strings.
 * An fd below <= 0 wont be closed, strings can be set to NULL.
 * 
 * @param fd The fd to be closed.
 * 
 * @param str2 The first string to be freed.
 * 
 * @param str2 The second string to be freed.
 * 
 * @param return_v The value this function wil return.
 * 
 * @return - [return_v] -
*/
int32_t	close_free_and_return(int32_t fd, char *str1, \
								char *str2, int32_t return_v)
{
	if (fd > 0)
	{
		if (close(fd) == -1)
			exit_with_error_message("close failed\n", NULL, NULL, 1);
	}
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (return_v);
}

/**
 * This function will create a fork to
 * run the heredoc in and handle its errors.
 * 
 * @param heredoc_path The path towards the heredoc file.
 *
 * @param delimiter Pointer to the string containing the heredoc delimiter.
 * 
 * @param type The type of heredoc (with or without expansion).
 * 
 * @param env Pointer to the environment variable list.
 * 
 * @return - [0] success - [-1] signal interupted / heredoc failed - 
*/
static int32_t	run_heredoc(const char *heredoc_path, \
						char *delimiter, int32_t type, t_env_vars *env)
{
	int32_t	return_of_heredoc;

	return_of_heredoc = 0;
	g_info.heredoc_breakout = false;
	g_info.heredoc_pid = fork();
	if (g_info.heredoc_pid == -1)
		exit_with_error_message("Fork failed\n", NULL, NULL, 1);
	else if (g_info.heredoc_pid == 0)
		read_input_and_write_to_heredoc(heredoc_path, delimiter, type, env);
	else
	{
		free(delimiter);
		signal(SIGINT, heredoc_handler);
		waitpid(g_info.heredoc_pid, &return_of_heredoc, 0);
		return_of_heredoc = WEXITSTATUS (return_of_heredoc);
		if (g_info.heredoc_breakout == true || return_of_heredoc != 0)
			return (-1);
		init_signals();
	}
	return (0);
}

/**
 * Function to remove the created heredoc files that are set
 * inside the heredoc linked list.
 * 
 * @param files Pointer to the head of the heredoc list.
 * 
 * @return N/A
*/
void	remove_heredoc_files(t_heredoc **files)
{
	t_heredoc	*next;

	if (!files || !*files)
		return ;
	while (*files)
	{
		next = (*files)->next;
		if ((*files)->path)
		{
			unlink((*files)->path);
			free((*files)->path);
		}
		free(*files);
		*files = next;
	}
}

/**
 * Function to handle heredocs.
 * Creates files to write to, and asks for user input on terminal.
 * 
 * @param actions Pointer to the action list.
 * 
 * @param file_paths Pointer to the head of the heredoc list.
 * 
 * @param env Pointer to the environment variable list.
 * 
 * @return - [0] success - [-1] an error occurred -
*/
int32_t	heredoc(t_action *actions, t_heredoc **file_paths, t_env_vars *env)
{
	char	*delimiter;

	while (actions)
	{
		if (actions->type == HDOCSPACE || actions->type == HDOCQUOTE)
		{
			delimiter = ft_strdup(actions->arg[0]);
			if (!delimiter)
				return (-1);
			if (create_heredoc_file(actions, file_paths) == -1)
			{
				free(delimiter);
				return (-1);
			}
			if (run_heredoc(actions->arg[0], delimiter, \
							actions->type, env) == -1)
				return (-1);
		}
		actions = actions->next;
	}
	return (0);
}
