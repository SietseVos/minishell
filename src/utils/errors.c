/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 14:46:26 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/05 15:00:45 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to add a character at the end of a string. 
 * This function assumes there is enough space for the char and will
 * segfault if there is not.
 * 
 * @param str Pointer to the string which will need the char at the end.
 * 
 * @param c Character that needs to be added to the end of the string.
 * 
 * @return - N/A -
*/
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

/**
 * Function to concatinate all string and character after one another,
 * and then print it out on the STDERR.
 * (would be a lot nicer if we could use va_list)
 * 
 * @param str1 Pointer to the first string to be added.
 * 
 * @param char1 Character that needs to be set after everything before it.
 * 
 * @param char2 Character that needs to be set after everything before it.
 * 
 * @param str2 Pointer to the final string to be added.
 * 
 * @return - N/A -
*/
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
	{
		write(STDERR_FILENO, "Malloc error\n", 14);
		return ;
	}
	ft_strlcat(error_message, str1, strlen);
	add_char_to_str(error_message, char1);
	add_char_to_str(error_message, char2);
	ft_strlcat(error_message, str2, strlen);
	write(STDERR_FILENO, error_message, strlen);
	free(error_message);
}

/**
 * Function to concatinate all string after one another,
 * and then print it out on the STDERR.
 * (would be a lot nicer if we could use va_list)
 * 
 * @param str1 Pointer to the first string to be added.
 * 
 * @param str2 Pointer to the second string to be added.
 * 
 * @param str3 Pointer to the final string to be added.
 * 
 * @return - N/A -
*/
void	write_error_with_strings(char *str1, char *str2, char *str3)
{
	int32_t	strlen;
	char	*error_message;

	if (!str1 && !str2 && !str3)
		return ;
	strlen = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1;
	error_message = ft_calloc(strlen, sizeof(char));
	if (!error_message)
	{
		write(STDERR_FILENO, "Malloc error\n", 14);
		return ;
	}
	ft_strlcat(error_message, str1, strlen);
	ft_strlcat(error_message, str2, strlen);
	ft_strlcat(error_message, str3, strlen);
	write(STDERR_FILENO, error_message, strlen);
	free(error_message);
}

/**
 * Function to write an error to the STDERR and return NULL.
 * This function adds newline after the given message.
 * 
 * @param errmsg Pointer to the string containing the error message.
 * 
 * @return - [NULL] -
*/
void	*nullerr(char *errmsg)
{
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	return (NULL);
}

/**
 * Function to write an error to the STDERR and return false.
 * This function adds a newline after the given message/
 * 
 * @param errmsg Pointer to the string containing the error message.
 * 
 * @return - [false] -
*/
bool	boolerr(char *errmsg)
{
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	return (false);
}
