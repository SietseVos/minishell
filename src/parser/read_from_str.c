#include "minishell.h"

int32_t	exit_status_numblen(int32_t *strlen, int32_t varlen)
{
	int32_t	cpy;

	cpy = g_exit_status;
	if (cpy == 0)
	{
		*strlen += 1;
		return (varlen);
	}
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

	// printf("interpeting variable strlen\n");
	varlen = envvarlen(str, c);
	if (varlen == 2 && str[1] == '?')
		return (exit_status_numblen(strlen, varlen));
	while (envp)
	{
		if (ft_strncmp(envp ->str, str + 1, varlen - 1) == 0
			&& envp ->str[varlen - 1] == '=')
		{
			*strlen += ft_strlen(envp ->str + varlen);
			break ;
		}
		envp = envp ->next;
	}
	return (varlen);
}

int32_t	strlen_til_space(char *str, env_vars_t *envp)
{
	int32_t	i;
	int32_t	strlen;

	i = 0;
	strlen = 0;
	while (is_whitespace(str[i]) == false && str[i] != '"'
		&& str[i] != '\'' && str[i] != '\0')
	{
		if (str[i] == '$')
			i += interpvar_strlen(str + i, ' ', &strlen, envp);
		else
		{
			strlen += 1;
			i++;
		}
	}
	return (strlen);
}

int32_t	strlen_til_quote(char *str, char c, env_vars_t *envp)
{
	int32_t	i;
	int32_t	strlen;

	i = 0;
	strlen = 0;
	while (str[i] != c && str[i] != '\0')
	{
		if (c == '"' && str[i] == '$')
			i += interpvar_strlen(str + i, c, &strlen, envp);
		else
		{
			strlen += 1;
			i++;
		}
	}
	return (strlen);
}

void	read_input_str(char *str, int *strlen, env_vars_t *envp)
{
	int32_t	strlentmp;

	while (*str != '\0' && *str != ' ')
	{
		strlentmp = 0;
		if (*str == '"' || *str == '\'')
		{
			strlentmp += strlen_til_quote(str + 1, *str, envp);
			if (*(str + strlentmp + 1) == '"')
				str += strlentmp + 2;
			else
				str += strlentmp + 1;
		}
		else
		{
			strlentmp += strlen_til_space(str, envp);
			str += strlentmp;
		}
		*strlen += strlentmp;
	}
}
