#include "minishell.h"

static void	add_char_to_str(char *str, char c)
{
	int32_t	i;

	i = 0;
	while (str[i])
		i++;
	if (c)
		str[i] = c;
	str[i + 1] = '\0';
}

void	write_error_with_chars(char *str1, char char1, char char2, char *str2)
{
	int32_t	strlen;
	int32_t	char_count;
	char	*error_message;

	char_count = 0;
	if (!str1 && !str2 && !char1 && !char2)
		return ;
	if (char1)
		char_count += 1;
	if (char2)
		char_count += 1;	
	strlen = ft_strlen(str1) + char_count + ft_strlen(str2) + 1;
	error_message = ft_calloc(strlen, sizeof(char));
	if (!error_message)
		return ;
	ft_strlcat(error_message, str1, strlen);
	add_char_to_str(error_message, char1);
	add_char_to_str(error_message, char2);
	ft_strlcat(error_message, str2, strlen);
	write(STDERR_FILENO, error_message, strlen);
	free(error_message);
}

void	write_error_with_strings(char *str1, char *str2, char *str3)
{
	int32_t	strlen;
	char	*error_message;

	if (!str1 && !str2 && !str3)
		return ;
	strlen = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1;
	error_message = ft_calloc(strlen, sizeof(char));
	if (!error_message)
		return ;
	ft_strlcat(error_message, str1, strlen);
	ft_strlcat(error_message, str2, strlen);
	ft_strlcat(error_message, str3, strlen);
	write(STDERR_FILENO, error_message, strlen);
	free(error_message);
}

void	*nullerr(char *errmsg)
{
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	return (NULL);
}

bool	boolerr(char *errmsg)
{
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	return (false);
}
