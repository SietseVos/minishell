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
	if (varlen == 1)
	{
		if (c == ' ' && (is_whitespace(str[1]) == true || str[1] == '\0'))
			*strlen += 1;
		else if (c == '"' || c == '\'')
			*strlen += 1;
		return (varlen);
	}
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

int32_t	strlen_til_space(char *str, env_vars_t *envp, int32_t *strlen)
{
	int32_t	i;

	i = 0;
	while (is_whitespace(str[i]) == false && str[i] != '"'
		&& str[i] != '\'' && str[i] != '\0')
	{
		printf("strlen_til_space is at: %c\n", str[i]);
		if (str[i] == '$')
		{
			printf("i before increment: %c\n", str[i]);
			i += interpvar_strlen(str + i, ' ', strlen, envp);
			printf("i after increment: %c\n", str[i]);
		}
		else
		{
			*strlen += 1;
			i++;
		}
	}
	return (i);
}

int32_t	strlen_til_quote(char *str, char c, env_vars_t *envp, int32_t *strlen)
{
	int32_t	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		printf("strlen_til_quote is at: %c\n", str[i]);
		if (c == '"' && str[i] == '$')
			i += interpvar_strlen(str + i, c, strlen, envp);
		else
		{
			*strlen += 1;
			i++;
		}
	}
	return (i);
}

void	read_input_str(char *str, int *strlen, env_vars_t *envp)
{
	while (*str != '\0' && is_whitespace(*str) == false)
	{
		if (*str == '"' || *str == '\'')
		{
			str += strlen_til_quote(str + 1, *str, envp, strlen);
			if (*(str + 1) == '"' || *(str + 1) == '\'')
				str += 2;
			else
				str += 1;
		}
		else
			str += strlen_til_space(str, envp, strlen);
		printf("stringlength: %d\n", *strlen);
	}
}
