#include "minishell.h"

int32_t	strlen_quote(char *str)
{
	int32_t	i;
	int32_t	ret;

	i = 0;
	ret = 0;
	while (str[i] != '\0')
	{
		ret++;
		i++;
	}
	return (ret);
}

int32_t	interpvar_strlen(char *str, char c, int32_t *strlen, env_vars_t *envp)
{
	int32_t	i;
	int32_t	varlen;

	i = 0;
	varlen = envvarlen(str, c);
	while (envp)
	{
		if (ft_strncmp(envp ->str, str + 1, varlen - 1) == 0 && envp ->str[varlen - 1] == '=')
		{
			*strlen += ft_strlen(envp ->str + varlen);
			break ;
		}
		envp = envp ->next;
	}
	return (varlen);
}

void	strlen_til_space(char *str, int32_t *strlen, env_vars_t *envp)
{
	int32_t	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
	{
		if (str[i] == '$')
			i += interpvar_strlen(str + i, ' ', strlen, envp);
		else
		{
			*strlen += 1;
			i++;
		}
	}
}

void	strlen_til_quote(char *str, int32_t *strlen, char c, env_vars_t *envp)
{
	int32_t	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		if (c == '"' && str[i] == '$')
			i += interpvar_strlen(str + i, c, strlen, envp);
		else
		{
			*strlen += 1;
			i++;
		}
	}
}

void	read_input_str(char *str, int *strlen, env_vars_t *envp)
{
	if (*str == '"')
	{
		strlen_til_quote(str + 1, strlen, '"', envp);
		return ;
	}
	else if (*str == '\'')
	{
		strlen_til_quote(str + 1, strlen, '\'', envp);
		return ;
	}
	strlen_til_space(str, strlen, envp);
}
