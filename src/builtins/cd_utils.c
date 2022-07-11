/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:22:54 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/11 14:27:35 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

t_global_info	g_info;

/**
 * Function to write a cd file / directory error
 * onto the stderr and set the exit status to 1.
 * 
 * @param str Pointer to the string containing the
 * argument that generated this error.
 * 
 * @return [1]
*/
int32_t	chdir_error(char *str, int32_t error)
{
	g_info.exit_status = 1;
	if (error == EACCES)
		write_error_with_strings("minishell: cd: ", str, \
								": Permission denied\n");
	else if (error == ENOENT)
		write_error_with_strings("minishell: cd: ", str, \
								": No such file or directory\n");
	else if (error == ENOTDIR)
		write_error_with_strings("minishell: cd: ", str, \
								": Not a directory\n");
	else
		write_error_with_strings("minishell: cd: ", str, \
								": Change directory error\n");
	return (1);
}

/**
 * This function copies the string inside pwd_node,
 * adds "OLD" in front and then places
 * it inside of oldpwd_node. 
 * 
 * @param *oldpwd_node Pointer to the node where
 * the string has the be placed.
 * 
 * @param *pwd_node Pointer to the node containing
 * the string that has to be copied.
 * 
 * @param *has_been_null Pointer to a boolian that
 * will be changed indicating it has not been set to null.
 * 
 * @return [-1] If memory allocation fails else [0].
*/
int32_t	move_pwd_to_oldpwd(t_env_vars *oldpwd_node, \
		t_env_vars *pwd_node, bool *has_been_null)
{
	int32_t	oldpwd_size;

	*has_been_null = false;
	free(oldpwd_node->str);
	oldpwd_node->str = NULL;
	oldpwd_size = strlen(pwd_node->str) + OLD + NULL_TERM;
	oldpwd_node->str = ft_calloc(oldpwd_size, sizeof(char));
	if (!oldpwd_node->str)
		return (-1);
	ft_strlcat(oldpwd_node->str, "OLD", oldpwd_size);
	ft_strlcat(oldpwd_node->str, pwd_node->str, oldpwd_size);
	return (0);
}

/**
 * Function to set the OLDPWD value to
 * the current working directory (before changing directories).
 * 
 * @param oldpwd_node Pointer to the OLDPWD node.
 * 
 * @return - [0] Success - [-1] Malloc fail -
*/
int32_t	set_oldpwd(t_env_vars *oldpwd_node)
{
	char	*cwd;

	free(oldpwd_node->str);
	oldpwd_node->str = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	oldpwd_node->str = create_new_cd_str("OLDPWD=", cwd);
	free(cwd);
	if (!oldpwd_node->str)
		return (-1);
	return (0);
}

/**
 * Function to set the OLDPWD node to contain
 * an empty string as value.
 * 
 * @param oldpwd_node Pointer to the OLDPWD node.
 * 
 * @param has_been_null Pointer to a static boolian
 * keeping track if the OLPWD node has already been null.
 * 
 * @return - [0] Success - [-1] Malloc fail -
*/
int32_t	create_empty_oldpwd(t_env_vars *oldpwd_node, bool *has_been_null)
{
	free(oldpwd_node->str);
	oldpwd_node->str = create_new_cd_str("OLDPWD=", NULL);
	oldpwd_node->has_value = true;
	*has_been_null = true;
	if (!oldpwd_node->str)
		return (-1);
	return (0);
}

/**
 * Function to create a new environment variable node
 * containing "OLPWD=".
 * 
 * @param env Pointer to the head of the envrionment variable list.
 * 
 * @return - [0] Success - [-1] Malloc fail -
*/
int32_t	create_new_oldpwd_node(t_env_vars **env)
{
	char	*old_pwd;

	old_pwd = ft_strdup("OLDPWD=");
	if (!old_pwd)
		return (-1);
	if (add_env_node(env, old_pwd) == -1)
	{
		free(old_pwd);
		return (-1);
	}
	return (0);
}
