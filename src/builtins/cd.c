
#include "minishell.h"

static void	str_add(char *take, char *place)
{
	int32_t i;
	int32_t	j;

	i = 0;
	j = 0;
	while (place[j])
		j++;
	while (take[i])
	{
		place[j] = take[i];
		i++;
		j++;
	}
	place[j] = '\0';
}

static char	*create_new_pwd_str(char *pwd, char *upfront)
{
	int32_t	strlen_pwd;
	int32_t	strlen_upfront;
	char	*new;

	strlen_pwd = ft_strlen(pwd);
	strlen_upfront = ft_strlen(upfront);
	new = ft_calloc(strlen_pwd + strlen_upfront + 3, sizeof(char));
	if (!new)
		return (NULL);
	if (upfront)
		str_add(upfront, new);
	if (pwd)
		str_add(pwd, new);
	return (new);
}

static int32_t	change_pwd_path(env_vars_t *env)
{
	env_vars_t	*path;
	char		*new_pwd;
	char		*pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);
	new_pwd = create_new_pwd_str(pwd, "PWD=");
	if (!new_pwd)
		return (-1);
	free(pwd);
	path = get_variable_node(env, "PWD=");
	if (path)
		path->str = new_pwd;
	else
		free(new_pwd);
	return (0);
}

static int32_t	change_old_pwd_path(env_vars_t *env, bool *has_been_null)
{
	env_vars_t	*oldpwd_node;
	env_vars_t	*pwd_node;
	char		*cwd;

	oldpwd_node = get_variable_node(env, "OLDPWD=");
	pwd_node = get_variable_node(env, "PWD=");
	if (oldpwd_node && pwd_node)
	{
		*has_been_null = false;
		free(oldpwd_node->str);
		oldpwd_node->str = ft_calloc(strlen(pwd_node->str + 4), sizeof(char));
		if (!oldpwd_node->str)
			return (-1);
		str_add("OLD", oldpwd_node->str);
		str_add(pwd_node->str, oldpwd_node->str);
	}
	else if (oldpwd_node && !pwd_node && *has_been_null)
	{
		free(oldpwd_node->str);
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (-1);
		oldpwd_node->str = create_new_pwd_str(cwd, "OLDPWD=");
		free(cwd);
	}
	else if (oldpwd_node && !pwd_node && !*has_been_null)
	{
		free(oldpwd_node->str);
		oldpwd_node->str = create_new_pwd_str(NULL, "OLDPWD=");
		*has_been_null = true;
	}
	if (pwd_node)
		free(pwd_node->str);
	return (0);
}

int32_t	cd(char **argument, env_vars_t *env)
{
	static bool	has_been_null = false;
	static bool	start_of_program = true;
	char		*old_pwd;

	if (start_of_program)
	{
		start_of_program = false;
		old_pwd = create_new_pwd_str(NULL, "OLDPWD=");
		if (add_env_node(env, old_pwd) == -1)
		{
			free(old_pwd);
			return (-1);
		}
	}
	if (change_old_pwd_path(env, &has_been_null) == -1)
		return (-1);
	if (chdir(argument[0]) != 0)
	{
		g_exit_status = 1;
		printf("bash: cd: %s: No such file or directory\n", argument[0]);
		return (1);
	}
	if (change_pwd_path(env) == -1)
		return (-1);	
	g_exit_status = 0;
	return (0);
}
// OLDPWD is the string of PWD before changing it, after calling cd the first time after unsetting PWD,
// OLDPWD will have an empty string, otherwise it will be filled with the last dir. 
// this proccess resets if PWD gets added with export again.
