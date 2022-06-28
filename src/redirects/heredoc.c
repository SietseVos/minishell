/* ************************************************************************** */
/*                                                                            */
/*                                                        :::::::::::::               */
/*   heredoc.c                                          :+:  :+:            */
/*                                                      +:+                         */
/*   By: rvan-mee <rvan-mee@student.42.fr>              +#+                         */
/*                                                                                    */
/*   Created: 2022/06/21 22:01:34 by rvan-mee      #+##+#    #+#                 */
/*   Updated: 2022/06/28 16:18:06 by svos      ########   odam   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int32_t	run_heredoc(const char *heredoc_path, \
						char *delimiter, int32_t type, env_vars_t *env)
{
	int32_t	fd;
	char	*in;

	// ctrl c signal should work run inside of fork
	in = NULL;
	g_info.heredoc_breakout = false;
	g_info.heredoc_pid = fork();
	if (g_info.heredoc_pid == -1)
		exit_with_error_message("fork failed\n", NULL, NULL, 1);
	if (g_info.heredoc_pid == 0)
	{
		fd = open(heredoc_path, O_WRONLY | O_TRUNC);
		if (fd == -1)
			return (-1);
		while (1)
		{
			in = readline("> ");
			if (!in)
				return (close_free_and_return(fd, delimiter, NULL, 0));
			if (ft_strcmp(delimiter, in) == 0)
				return (close_free_and_return(fd, delimiter, in, 0));
			if (expand_heredoc(&in, type, env) == -1)
				return (close_free_and_return(fd, delimiter, in, -1));
			else if (write(fd, in, ft_strlen(in)) == -1 || write(fd, "\n", 1) == -1)
				return (close_free_and_return(fd, delimiter, in, -1));
			free(in);
		}
	}
	else
	{
		signal(SIGINT, heredoc_handler);
		waitpid(g_info.heredoc_pid, NULL, 0);
		if (g_info.heredoc_breakout == true)
			return (-1);
	}
	return (0);
}

void	remove_heredoc_files(heredoc_t **files)
{
	heredoc_t	*next;

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

int32_t	heredoc(action_t *actions, heredoc_t **file_paths, env_vars_t *env)
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
