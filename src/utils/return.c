/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   return.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 22:02:44 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/25 14:43:24 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	close_fd_return_error(char *error_message, int32_t fd, \
		int32_t return_value)
{
	close(fd);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	return (return_value);
}

void	exit_with_error_message(char *str1, char *str2, char *str3, \
		int32_t exit_value)
{
	int32_t	strlen;
	char	*error_message;

	if (!str1 && !str2 && !str3)
		exit (exit_value);
	strlen = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1;
	error_message = ft_calloc(strlen, sizeof(char));
	if (!error_message)
		exit (exit_value);
	ft_strlcat(error_message, str1, strlen);
	ft_strlcat(error_message, str2, strlen);
	ft_strlcat(error_message, str3, strlen);
	write(STDERR_FILENO, error_message, strlen);
	free(error_message);
	exit (exit_value);
}

int32_t	return_with_error_message(char *str1, const char *str2, char *str3, \
		int32_t return_value)
{
	int32_t	strlen;
	char	*error_message;

	if (!str1 && !str2 && !str3)
		return (return_value);
	strlen = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1;
	error_message = ft_calloc(strlen, sizeof(char));
	if (!error_message)
		return (return_value);
	ft_strlcat(error_message, str1, strlen);
	ft_strlcat(error_message, str2, strlen);
	ft_strlcat(error_message, str3, strlen);
	write(STDERR_FILENO, error_message, strlen);
	free(error_message);
	return (return_value);
}
