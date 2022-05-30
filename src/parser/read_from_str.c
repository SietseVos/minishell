#include "minishell.h"

int32_t	strlen_quote(char *str)
{
	int32_t	i;
	int32_t	ret;

	i = 0;
	ret = 0;
	printf("str to count: %s\n", str);
	// while (str[i] != '=')
	// 	i++;
	// i++;
	while (str[i] != '\0')
	{
		ret++;
		i++;
	}
	printf("strlen of envvar in strlen_quote: %d\n", ret);
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
			printf("found environment variable: %s\n", envp ->str + varlen - 1);
			*strlen += strlen_quote(envp ->str + varlen);
			break ;
		}
		envp = envp ->next;
	}
	printf("interpvar_strlen is returning: %d\n", varlen);
	return (varlen);
}

int32_t	strlen_til_space(char *str, int32_t *strlen, env_vars_t *envp)
{
	int32_t	endskip;
	int32_t	i;

	i = 0;
	endskip = 0;
	printf("entered strlen_til_space function\n");
	while (str[i] != ' ' && str[i] != '\0')
	{
		if (str[i] == '$')
			i += interpvar_strlen(str + i, ' ', strlen, envp);
		else
		{
			*strlen += 1;
			i++;
		}
		// printf("counting char: %c in strlen_til_space\n", str[i]);
	}
	if (str[i] != '\0')
		endskip += 1;
	return (endskip);
}

int32_t	strlen_til_quote(char *str, int32_t *strlen, char c, env_vars_t *envp)
{
	int32_t	endskip;
	int32_t	i;

	i = 0;
	endskip = 0;
	while (str[i] != c && str[i] != '\0')
	{
		if (c == '"' && str[i] == '$')
		{
			printf("i and strlen bofore interpeting var strlen: %d, %d\n", i, *strlen);
			i += interpvar_strlen(str + i, c, strlen, envp);
			printf("i and strlen after interpeting var strlen: %d, %d\n", i, *strlen);
			printf("pointer pointing to : -%c-\n", str[i]);
		}
		else
		{
			*strlen += 1;
			i++;
		}
	}
	printf("strlen in strlen_til_qoute: %d\n", *strlen);
	while (endskip <= 2 && str[i + endskip] != '\0')
		endskip++;
	return (endskip);
}

int32_t	read_input_str(char *str, int *strlen, env_vars_t *envp)
{
	if (*str == '"')
		return (strlen_til_quote(str + 1, strlen, '"', envp));
	else if (*str == '\'')
		return (strlen_til_quote(str + 1, strlen, '\'', envp));
	return (strlen_til_space(str, strlen, envp));
}
