
#include "minishell.h"

static int32_t	get_total_str_len(char *input, env_vars_t *env)
{
	int32_t	len;
	int32_t	i;

	i = 0;
	len = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] != ' ')
		{
			i += interpvar_strlen(&input[i], '\0', &len, env);
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

int32_t	expand_heredoc(char *input, int32_t type, env_vars_t *env)
{
	int32_t	total_new_str_len;
	char	*new_str;
	int32_t	i;
	int32_t	j;

	i = 0;
	j = 0;
	if (type == HDOCSPACE)
		return (0);
	total_new_str_len = get_total_str_len(input, env);
	new_str = ft_calloc(total_new_str_len, sizeof(char));
	if (!new_str)
		return (-1);
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == ' ')
		{
			i += place_envvar_space(&new_str[j], &input[i], env, &j);
			continue ;
		}
		new_str[j] = input[i];
		i++;
		j++;
	}
	free(input);
	input = new_str;
	return (0);
}

int32_t	read_heredoc_input(int32_t fd, char *delimiter, char **in)
{
	*in = readline("> ");
	if (!*in)
		return (close_free_and_return(fd, delimiter, NULL, 0));
	else if (*in[0] == '\0')
	{
		if (write(fd, "\n", 1) == -1)
			return (close_free_and_return(fd, delimiter, *in, -1));
		return (close_free_and_return(fd, delimiter, *in, 2));
	}
	printf("input inside readline: %s\n", *in);
	return (1);
}
