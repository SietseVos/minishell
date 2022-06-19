
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
		exit (1);
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
