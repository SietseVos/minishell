
#include "minishell.h"

static char	*get_hex_value(unsigned long num)
{
	char	*str;
	int32_t	i;

	i = 11;
	str = ft_calloc(13, sizeof(char));
	if (!str)
		return (NULL);
	while (num > 0)
	{
		if (num % 16 < 10)
			str[i] = num % 16 + '0';
		else
			str[i] = num % 16 + 'a' - 10;
		num /= 16;
		i--;
	}
	return (str);
}

static void	set_heredoc_path_in_node(action_t *heredoc_node, char *path)
{
	free(heredoc_node->arg[0]);
	heredoc_node->arg[0] = path;
}

int	errorno;

int32_t	create_heredoc_file(action_t *heredoc_node)
{
	int32_t	fd;
	char	*pointer_address;
	char	*path;

	path = ft_calloc(32, sizeof(char));
	if (!path)
		return (-1);
	pointer_address = get_hex_value((unsigned long)heredoc_node->arg[0]);
	if (!pointer_address)
		return (-1);
	ft_bzero(path, 32);
	ft_strlcat(path, "tmp_heredoc0x", 32);
	ft_strlcat(path, pointer_address, 32);
	free(pointer_address);
	set_heredoc_path_in_node(heredoc_node, path);
	fd = open(path, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
	{
		printf("creation of heredoc %s failed errorno %d\n", path, errorno);
		return (-1);
	}
	close(fd);
	return (0);
}
