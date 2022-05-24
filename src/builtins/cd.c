
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

static char	*create_new_pwd_str(char *pwd)
{
	char	*new;
	int32_t		strlen;

	strlen = ft_strlen(pwd);
	new = malloc(sizeof(char) * (strlen + 8));
	if (!new)
		exit(404);
	str_add("PATH=\"", new);
	str_add(pwd, new);
	str_add("\"", new);
	free(pwd);
	return (new);
}

static void	change_pwd_path(env_vars_t *env)
{
	char	*new_pwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	new_pwd = create_new_pwd_str(pwd);
	while (env)
	{
		if (ft_strncmp(env->str, "PATH=", 5) == 0)
		{
			free(env->str);
			env->str = new_pwd;
		}
		env = env->next;
	}
}

void	cd(char **argument, env_vars_t *env)
{
	if (chdir(argument[0]) != 0)
	{
		// set exit value 1
		printf("bash: cd: %s: No such file or directory\n", argument[0]);
		return ;
	}
	change_pwd_path(env);
}
