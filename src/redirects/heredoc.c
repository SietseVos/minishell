/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 20:03:45 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 21:49:35 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Lazy strncmp without the need to specify the size to compare.
 * 
 * @param str1 The first string to compare.
 * 
 * @param str2 The second string to compare against the first.
 * 
 * @return - [0] strings are equal - [-1] strings differ -
*/
static int32_t	ft_strcmp(char *str1, char *str2)
{
	int32_t	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	if (str1[i] != str2[i])
		return (-1);
	return (0);
}

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
 * This function will run the heredoc, get the input from terminal
 * and write it into a file.
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
	int32_t	fd;
	char	*in;

	// ctrl c signal inside of fork works now?? test more..
	in = NULL;
	g_info.heredoc_breakout = false;
	g_info.heredoc_pid = fork();
	if (g_info.heredoc_pid == -1)
		exit_with_error_message("Fork failed\n", NULL, NULL, 1);
	else if (g_info.heredoc_pid == 0)
	{
		fd = open(heredoc_path, O_WRONLY | O_TRUNC);
		if (fd == -1)
			exit (-1);
		while (1)
		{
			in = readline("> ");
			if (!in)
				exit (close_free_and_return(fd, delimiter, NULL, 0));
			if (ft_strcmp(delimiter, in) == 0)
				exit (close_free_and_return(fd, delimiter, in, 0));
			if (expand_heredoc(&in, type, env) == -1)
				exit (close_free_and_return(fd, delimiter, in, -1));
			else if (write(fd, in, ft_strlen(in)) == -1 || write(fd, "\n", 1) == -1)
				exit (close_free_and_return(fd, delimiter, in, -1));
			free(in);
		}
	}
	else
	{
		signal(SIGINT, heredoc_handler);
		waitpid(g_info.heredoc_pid, NULL, 0);
		if (g_info.heredoc_breakout == true ) // || return value of child != 0)
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
