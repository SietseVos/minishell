#include "minishell.h"

int32_t	exit_status_numblen(int32_t *strlen, int32_t varlen)
{
	int32_t	cpy;

	cpy = g_exit_status;
	while (cpy > 0)
	{
		cpy = cpy / 10;
		*strlen += 1;
	}
	return (varlen);
}

int32_t	interpvar_strlen(char *str, char c, int32_t *strlen, env_vars_t *envp)
{
	int32_t	varlen;

	varlen = envvarlen(str, c);
	if (varlen == 2 && str[1] == '?')
		return (exit_status_numblen(strlen, varlen));
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
