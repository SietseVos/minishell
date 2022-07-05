/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   more_errors.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:44:35 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/05 18:59:24 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to write an error that the HOME path is not set.
 * Sets the exit status to 1.
 * 
 * @param N/A
 * 
 * @return - [0] -
*/
int32_t	cd_home_path_not_set(void)
{
	g_info.exit_status = 1;
	write(STDERR_FILENO, "minishell: cd: HOME not set\n", 29);
	return (0);
}
