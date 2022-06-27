#include "minishell.h"

bool	check_ambigu(char *input, int32_t i, env_vars_t *envp, char c)
{
	int32_t	len;

	len = envvarlen(input + i, c);
	while (envp)
	{
		if (ft_strncmp(envp ->str, input + i + 1, len - 1) == 0
			&& envp ->str[len - 1] == '=')
			return (false);
		envp = envp ->next;
	}
	if (input[i + len] == '\0')
		return (true);
	if (c == ' ' && (input[i + len] == ' ' || input[i + len] == '\0'))
		return (true);
	if ((c == '"' || c == '\'') && (input[i + len] == c))
	{
		i++;
		if (input[i + len] == ' ' || input[i + len] == '\0')
			return (true);
	}
	return (false);
}

bool	ambigu_redirect(char *input, int32_t i, env_vars_t *envp)
{
	skip_operator_space(input, &i);
	if (input[i] != '"' && input[i] != '\'' && input[i] != '$')
		return (false);
	if (input[i] == '\0')
		return (false);
	if (input[i] == '$')
		return (check_ambigu(input, i, envp, ' '));
	else if ((input[i] == '"' || input[i] == '\'') && input[i + 1] == '$')
		return (check_ambigu(input, i + 1, envp, input[i]));
	return (false);
}

action_t	*create_ambigu_node(int32_t size)
{
	action_t	*ret;

	ret = malloc(sizeof(action_t));
	if (ret == NULL)
		return (NULL);
	ret->arg = malloc(sizeof(char *) * 2);
	if (ret->arg == NULL)
	{
		free(ret);
		return (NULL);
	}
	ret->arg[0] = malloc(sizeof(char) * size + 1);
	if (ret ->arg[0] == NULL)
	{
		free(ret->arg);
		free(ret);
		return (NULL);
	}
	ret->type = AMBIGU;
	ret->arg[1] = NULL;
	return (ret);
}

action_t	*found_ambigu(char *input, int32_t *i)
{
	int32_t		len;
	int32_t		j;
	action_t	*ret;

	j = 0;
	skip_operator_space(input, i);
	if (input[*i] == '"' || input[*i] == '\'')
		*i += 1;
	len = envvarlen(input + *i + 1, ' ');
	ret = create_ambigu_node(len + 1);
	if (ret == NULL)
		return (nullerr("failed to malloc ambigu node"));
	while (j <= len)
	{
		ret->arg[0][j] = input[*i];
		j++;
		*i += 1;
	}
	ret->arg[0][j] = '\0';
	if (input[*i] == '"' || input[*i] == '\'')
		*i += 1;
	while (is_whitespace(input[*i]) == true)
		*i += 1;
	return (ret);
}
