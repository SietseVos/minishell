#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
# define TRUNC 0
# define PIPE 1
# define APPEND 2
# define HDOC 3
# define INFILE 4
# define OUTFILE 5
# define TOSTDOUT 6
# define NOINPUT 7

typedef struct action_s
{
	char			**arg;
	int				type;
	struct action_s *next;
}	action_t;

char	*putstr(char **s, char c);
char	**ft_split(char *s, char c);



action_t	*determine_type(char *input, int *i)
{
	if (input[*i] == '<')
		return (prs_infile(input, i));
	else if (input[*i] == '>' || (input[*i] == '>' && input[*i + 1] == '>'))
		return (prs_outfile(input, i));
	else if (input[*i] == '<' && input[*i + 1] == '<')
		return (prs_hdoc(input, i));
	return (prs_cmd(input, i));
}

action_t	*parser(char *input)
{
	int			i;
	action_t	*ret;

	i = 0;
	ret = determine_type(input, &i);
	while (input[i])
	{
		ret ->next = determine_type(input, &i);
	}
}

int	main(char **envp)
{
	char	*input;
	action_t	*cmdseq;

	input = strdup("test input");
	cmdseq = parser(input);
}