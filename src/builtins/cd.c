/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 20:41:21 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/07/11 14:27:22 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

t_global_info	g_info;

/**
 * This function concatinates the given strings into one, newly allocated string.
 * It does not free any of the given strings.
 * 
 * @param var Variable to be in front of the working directory.
 * 
 * @param pwd Path of working directory.
 * 
 * @return [NULL] if allocation fails, otherwise the new string.
*/
char	*create_new_cd_str(char *var, char *pwd)
{
	int32_t	strlen_pwd;
	int32_t	strlen_var;
	int32_t	new_str_size;
	char	*new;

	strlen_pwd = ft_strlen(pwd);
	strlen_var = ft_strlen(var);
	new_str_size = strlen_pwd + strlen_var + NULL_TERM;
	new = ft_calloc(new_str_size, sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcat(new, var, new_str_size);
	ft_strlcat(new, pwd, new_str_size);
	return (new);
}

/**
 * Function to change the contents of the PWD node
 * inside the environment variables to the current working
 * directory. If PWD node does not exist it will return 1.
 * 
 * @param env Pointer to the environment variable list.
 * 
 * @return - [0] Success - [1] PWD node does not exist - 
 * [-1] Malloc fail -
*/
static int32_t	change_pwd_path(t_env_vars *env)
{
	t_env_vars	*path;
	char		*new_pwd;
	char		*pwd;

	path = get_variable_node(env, "PWD");
	if (!path)
		return (1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);
	new_pwd = create_new_cd_str("PWD=", pwd);
	free(pwd);
	if (!new_pwd)
		return (-1);
	free(path->str);
	path->str = new_pwd;
	return (0);
}

/**
 * This function takes the contents of the PWD
 * node and sets it inside the OLDPWD node.
 * If PWD does not exist and OLDPWD has not been empty yet
 * it sets the OLWPWD node to en empty string.
 * If OLDPWD has been empty and PWD does not exist it will
 * set it to the last working directory.
 * if neither exist it continues regularly.
 * 
 * @param env Pointer to the environment list containing the nodes.
 * 
 * @param has_been_null Pointer to a static boolian keeping
 * track of the OLDPWD string and if it has been set to NULL yet.
 * 
 * @return - [0] Success - [-1] Malloc fail -
*/
static int32_t	change_old_pwd_path(t_env_vars *env, bool *has_been_null)
{
	t_env_vars	*oldpwd_node;
	t_env_vars	*pwd_node;

	oldpwd_node = get_variable_node(env, "OLDPWD");
	pwd_node = get_variable_node(env, "PWD");
	if (oldpwd_node && pwd_node)
	{
		if (move_pwd_to_oldpwd(oldpwd_node, pwd_node, has_been_null) == -1)
			return (-1);
	}
	else if (oldpwd_node && !pwd_node && *has_been_null)
	{
		if (set_oldpwd(oldpwd_node) == -1)
			return (-1);
	}
	else if (oldpwd_node && !pwd_node && !*has_been_null)
	{
		if (create_empty_oldpwd(oldpwd_node, has_been_null) == -1)
			return (-1);
	}
	return (0);
}

/**
 * If cd has not been called before this function will run.
 * It takes the OLDPWD env node (if it exists) or creates one
 * and sets its value to true, containing an empty string.
 * 
 * @param start_of_program Pointer to a static boolian
 * that keeps track if it is the first cd call.
 * 
 * @param env Pointer to the head of the
 * environment variable list.
 * 
 * @return - [0] Success - [-1] Malloc fail -
*/
static int32_t	first_cd_call(bool *start_of_program, t_env_vars **env)
{
	t_env_vars	*oldpwd_node;

	oldpwd_node = get_variable_node(*env, "OLDPWD");
	if (*start_of_program == false)
		return (0);
	*start_of_program = false;
	if (oldpwd_node)
	{
		oldpwd_node->has_value = true;
		free(oldpwd_node->str);
		oldpwd_node->str = ft_strdup("OLDPWD=");
		if (!oldpwd_node->str)
			return (-1);
	}
	else
	{
		if (create_new_oldpwd_node(env) == -1)
			return (-1);
	}
	return (0);
}

/**
 * Builtin function to change the current working directory.
 * 
 * @param argument Double character array
 * containing all arguments to execute.
 * 
 * @param env Pointer to the head of the
 * environment variable list.
 * 
 * @return - [0] Success - [1] Function could not succeed - 
 *[-1] Malloc fail -
*/
int32_t	cd(char **argument, t_env_vars **env)
{
	static bool	has_been_null = false;
	static bool	start_of_program = true;
	t_env_vars	*home_path;

	if (!*argument || argument[0][0] == '\0')
	{
		home_path = get_variable_node(*env, "HOME");
		if (!home_path || home_path->has_value == false)
			return (cd_home_path_not_set());
		else if (home_path->str[5] == '\0')
			return (0);
		else if (chdir(&home_path->str[5]) != 0)
			return (chdir_error(&home_path->str[5], errno));
	}
	else if (chdir(argument[0]) != 0)
		return (chdir_error(argument[0], errno));
	if (first_cd_call(&start_of_program, env) == -1
		|| change_old_pwd_path(*env, &has_been_null) == -1
		|| change_pwd_path(*env) == -1)
		return (-1);
	g_info.exit_status = 0;
	return (0);
}
