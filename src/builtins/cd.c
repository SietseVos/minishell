
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

static char	*create_new_pwd_str(char *pwd, char *var)
{
	int32_t	strlen_pwd;
	int32_t	strlen_var;
	char	*new;

	strlen_pwd = ft_strlen(pwd);
	strlen_var = ft_strlen(var);
	new = malloc(sizeof(char) * (strlen_pwd + strlen_var + 3));
	if (!new)
		exit(404);
	new[0] = '\0';
	str_add(var, new);
	str_add("\"", new);
	str_add(pwd, new);
	str_add("\"", new);
	free(pwd);
	return (new);
}

static void	change_pwd_path(env_vars_t *env)
{
	env_vars_t	*path;
	char		*new_pwd;
	char		*pwd;
	
	pwd = getcwd(NULL, 0);
	new_pwd = create_new_pwd_str(pwd, "PWD=");
	path = get_variable_node(env, "PWD=");
	if (path)
	{
		free(path->str);
		path->str = new_pwd;
	}
}

void	change_old_pwd_path(env_vars_t *env, char *old_pwd)
{
	env_vars_t	*path;
	char		*new_old_pwd;
	
	new_old_pwd = create_new_pwd_str(old_pwd, "OLDPWD=");
	path = get_variable_node(env, "OLDPWD=");
	if (path)
	{
		free(path->str);
		path->str = new_old_pwd;
	}
}

void	cd(char **argument, env_vars_t *env)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(argument[0]) != 0)
	{
		g_exit_status = 1;
		free(old_pwd);
		printf("bash: cd: %s: No such file or directory\n", argument[0]);
		return ;
	}
	change_old_pwd_path(env, old_pwd);
	change_pwd_path(env);
}
