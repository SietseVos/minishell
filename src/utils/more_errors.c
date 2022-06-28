/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   more_errors.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:44:35 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/06/28 16:21:24 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	cd_home_path_not_set(void)
{
	g_info.exit_status = 1;
	write(STDERR_FILENO, "bash: cd: HOME not set\n", 24);
	return (0);
}
