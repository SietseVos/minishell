/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 17:35:07 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/08 15:45:44 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

/**
 * Function to display the encountered error with the open
 * funciton. Sets the exit status to 1.
 * 
 * @param path Pointer to the string containing the path causing the error.
 * 
 * @param error The errno that open set.
 * 
 * @return - [-1] -
*/
int32_t	open_error(char *path, int32_t error)
{
	g_info.exit_status = 1;
	if (error == EACCES)
		write_error_with_strings("minishell: ", path, \
		": Premission denied\n");
	else if (error == EISDIR)
		write_error_with_strings("minishell: ", path, \
		": Is a directory\n");
	else if (error == ENOENT)
		write_error_with_strings("minishell: ", path, \
		": No such file or directory\n");
	else
		write_error_with_strings("minishell: ", path, \
		": open error\n");
	return (-1);
}
