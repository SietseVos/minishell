
#include "minishell.h"

/*
	*	This function concatinates the given strings into one, newly allocated string.
	*	It does not free any of the given strings.
	*	@param var Variable to be in front of the working directory.
	*	@param pwd Path of working directory.
	*	@return [NULL] if allocation fails, otherwise the new string.
*/
char	*create_new_cd_str(char *var, char *pwd)
{
	int32_t	strlen_pwd;
	int32_t	strlen_var;
	int32_t	new_str_size;
	char	*new;

	strlen_pwd = ft_strlen(pwd);
	strlen_var = ft_strlen(var);
	new_str_size = strlen_pwd + strlen_var + null;
	new = ft_calloc(new_str_size, sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcat(new, var, new_str_size);
	ft_strlcat(new, pwd, new_str_size);
	return (new);
}

static int32_t	change_pwd_path(env_vars_t *env)
{
	env_vars_t	*path;
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

static int32_t	change_old_pwd_path(env_vars_t *env, bool *has_been_null)
{
	env_vars_t	*oldpwd_node;
	env_vars_t	*pwd_node;

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
	// if (pwd_node)
	// 	free(pwd_node->str);
	return (0);
}

static int32_t	first_cd_call(bool *start_of_program, env_vars_t *env)
{
	env_vars_t	*oldpwd_node;
	char 		*old_pwd;

	oldpwd_node = get_variable_node(env, "OLDPWD");
	if (*start_of_program == false)
		return (0);
	*start_of_program = false;
	if (oldpwd_node)
	{
		oldpwd_node->has_value = true;
		free(oldpwd_node->str);
		oldpwd_node->str = NULL;
		oldpwd_node->str = ft_strdup("OLDPWD=");
		if (!oldpwd_node->str)
			return (-1);
	}
	else
	{
		old_pwd = ft_strdup("OLDPWD=");
		if (!old_pwd)
			return (-1);
		if (add_env_node(env, old_pwd) == -1)
		{
			free(old_pwd);
			return (-1);
		}
	}
	return (0);
}

int32_t	cd(char **argument, env_vars_t *env)
{
	static bool	has_been_null = false;
	static bool	start_of_program = true;
	env_vars_t *home_path;

	if (!*argument)
	{
		home_path = get_variable_node(env, "HOME");
		if (!home_path || home_path->has_value == false)
		{
			g_exit_status = 1;
			printf("bash: cd: HOME not set\n");
			return (0);
		}
		else if (home_path->str[5] == '\0')			// unset HOME then export HOME=
			return (0);
		else if (chdir(&home_path->str[5]) != 0)
			return (chdir_error(&home_path->str[5]));
	}
	else if (chdir(argument[0]) != 0)
		return (chdir_error(argument[0]));
	if (first_cd_call(&start_of_program, env) == -1
		|| change_old_pwd_path(env, &has_been_null) == -1
		|| change_pwd_path(env) == -1)
		return (-1);	
	g_exit_status = 0;
	return (0);
}
// OLDPWD is the string of PWD before changing it, after calling cd the first time after unsetting PWD,
// OLDPWD will have an empty string, otherwise it will be filled with the last dir. 
// this proccess resets if PWD gets added with export again.
