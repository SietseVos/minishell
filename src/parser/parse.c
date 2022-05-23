#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
# define INFILE 0
# define OUTFILE 1
# define APPEND 2
# define HDOC 3
# define TRUNC 4
# define PIPE 5
# define TOSTDOUT 6
# define NOINPUT 7

typedef struct action_s
{
	char			*arg;
	int				type;
	struct action_s *next;
}	action_t;

// char	*putstr(char **s, char c);
// char	**ft_split(char *s, char c);

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(src);
	while (*src != 0)
	{
		if (i + 1 < dstsize)
		{
			*dst = *src;
			dst++;
		}
		i++;
		src++;
	}
	if (dstsize != 0)
		*dst = '\0';
	return (len);
}


int	check_str_end(char *str, int i, int n)
{
	int	count;

	count = 0;
	while (count <= n)
	{
		if (str[i + count] == '\0')
			return (count);
		count++;
	}
	return (-1);
}

void	*nullerr(char *errmsg)
{
	printf("%s\n",errmsg);
	return (NULL);
}

int	strlen_til_space(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i] != ' ' && str[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

int	strlen_til_quote(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i] != '"' && str[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

action_t	*found_redirect(char *input, int *i, int type)
{
	action_t	*node;
	int			strlen;

	while (input[*i] != ' ')
		*i += 1;
	*i += 1;
	strlen = strlen_til_space(input, *i);
	if (input[*i] == '"')
	{
		*i += 1;
		strlen = strlen_til_quote(input, *i);
	}
	if (strlen == 0 || is_operator(input[*i]) == 1)
		return (nullerr("no string after space of redirect"));
	node = malloc(sizeof(action_t));
	if (node == NULL)
		return (nullerr("node malloc fail"));
	node ->arg = malloc(sizeof(char) * strlen + 1);
	if (node ->arg == NULL)
	{
		free(node);
		return (nullerr("node arg malloc fail"));
	}
	ft_strlcpy(node ->arg, input + *i, strlen + 1);
	node ->type = type;
	return (node);
}

action_t	*parse_file(char *input, int *i)
{
	action_t	*node;

	if (check_str_end(input, *i, 2) >= 0)
		return (nullerr("no string after redirect"));
	if (input[*i] == '<' && input[*i + 1] == ' ')
		node = found_redirect(input, i, INFILE);
	if (input[*i] == '>' && input[*i + 1] == ' ')
		node = found_redirect(input, i, OUTFILE);
	if (input[*i] == '<' && input[*i + 1] == '<')
		node = found_redirect(input, i, HDOC);
	if (input[*i] == '>' && input[*i + 1] == '>')
		node = found_redirect(input, i, APPEND);
	return (node);
}

action_t	*determine_type(char *input, int *i)
{
	if (input[*i] == '<' || input[*i] == '>')
		return (parse_file(input, i));
	// return (parse_cmd(input, i));
	return (NULL);
}

action_t	*parser(char *input)
{
	int			i;
	action_t	*ret;

	i = 0;
	ret = determine_type(input, &i);
	// while (input[i])
	// {
	// 	ret ->next = determine_type(input, &i);
	// }
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	action_t	*cmdseq;

	input = strdup("< \"jkdfjds\"   dsf");
	cmdseq = parser(input);
	printf("arg: %s, type: %d\n", cmdseq ->arg, cmdseq ->type);
	(void)argc;
	(void)argv;
}