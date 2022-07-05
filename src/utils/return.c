/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   return.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 22:02:44 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/05 19:20:52 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to close the given fd, write the given error message to the STDERR
 * and return with the given return_value.
 * 
 * @param error_message Pointer to the string containing the error message.
 * 
 * @param fd The fd that needs to be closed.
 * 
 * @param return_value The integer used as a return value for this function.
 * 
 * @return - [return_value] success - [exit 1] close failed - 
*/
int32_t	close_fd_return_error(char *error_message, int32_t fd, \
		int32_t return_value)
{
	if (close(fd) == -1)
		exit_with_error_message("close failed\n", NULL, NULL, 1);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	return (return_value);
}

/**
 * Function used to exit but with an error message written up front.
 * This function will concatinate all the given strings after one another
 * and then print it out on the STDERR.
 * 
 * @param str1 Pointer to the first error string to append after one another.
 * 
 * @param str1 Pointer to the second error string to append after one another.
 * 
 * @param str1 Pointer to the last error string to append after one another.
 * 
 * @param exit_value The value used to exit.
 * 
 * @return - [exit exit_value] -
*/
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

/**
 * Function used to return but with an error message written before it does so.
 * This function will concatinate all the given strings after one another
 * and then print it out on the STDERR.
 * 
 * @param str1 Pointer to the first error string to append after one another.
 * 
 * @param str1 Pointer to the second error string to append after one another.
 * 
 * @param str1 Pointer to the last error string to append after one another.
 * 
 * @param return_value The value used to return.
 * 
 * @return - [return_value] -
*/
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
