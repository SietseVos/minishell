#include "minishell.h"

void	interp_exit_status(char *dst, int32_t *i)
{
	int32_t	j;
	int32_t	cpy;

	j = 0;
	cpy = g_info.exit_status;
	if (cpy == 0)
	{
		dst[j] = '0';
		*i += 1;
		return ;
	}
	while (cpy > 0)
	{
		cpy = cpy / 10;
		j++;
	}
	cpy = g_info.exit_status;
	j--;
	while (cpy > 0)
	{
		dst[j] = cpy % 10 + '0';
		cpy = cpy / 10;
		j--;
		*i += 1;
	}
}

int32_t	copy_envvar_to_str(char *dst, char *src,
			t_env_vars *envp, int32_t varlen)
{
	int32_t	ret;

	ret = 0;
	while (envp)
	{
		if (ft_strncmp(envp ->str, src + 1, varlen - 1) == 0
			&& envp ->str[varlen - 1] == '=')
		{
			ft_strlcpy(dst, envp ->str + varlen,
				ft_strlen(envp ->str + varlen) + 1);
			ret += ft_strlen(envp ->str + varlen);
		}
		envp = envp ->next;
	}
	return (ret);
}

int32_t	place_envvar_quote(char *dst, char *src, t_env_vars *envp, int32_t *j)
{
	int32_t	varlen;

	varlen = envvarlen(src, '"');
	if (varlen == 2 && src[1] == '?')
	{
		interp_exit_status(dst, j);
		return (varlen);
	}
	if (varlen == 1)
	{
		*dst = '$';
		*j += 1;
		return (varlen);
	}
	*j += copy_envvar_to_str(dst, src, envp, varlen);
	return (varlen);
}

int32_t	place_envvar_space(char *dst, char *src, t_env_vars *envp, int32_t *j)
{
	int32_t	varlen;

	varlen = envvarlen(src, '"');
	if (varlen == 2 && src[1] == '?')
	{
		interp_exit_status(dst, j);
		return (varlen);
	}
	if (varlen == 1)
	{
		if (is_whitespace(src[1]) == true || src[1] == '\0')
		{
			*dst = '$';
			*j += 1;
		}
		return (varlen);
	}
	*j += copy_envvar_to_str(dst, src, envp, varlen);
	return (varlen);
}
