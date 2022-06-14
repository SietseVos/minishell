#include "minishell.h"

int32_t	count_strings(char **arr)
{
	int32_t	count;

	count = 0;
	while (*arr != NULL)
	{
		count++;
		arr++;
	}
	return (count);
}

char	**join_chararrs(char **arr1, char **arr2)
{
	int32_t	strcount;
	char	**ret;

	strcount = count_strings(arr1) + count_strings(arr2);
	ret = malloc(strcount);
	if (ret == NULL)
		return (nullerr("failed to malloc ret for join_chararrs"));
	ret[0] = ft_strdup("this has been put into string");
	ret[1] = NULL;
	return (ret);
}

bool	merge_nodes(action_t *dst, action_t **src, action_t **prevnextptr)
{
	char	**fragdst;
	char	**fragsrc;

	fragdst = dst->arg;
	fragsrc = (*src)->arg;
	dst->arg = join_chararrs(fragdst, fragsrc);
	(void)prevnextptr;

	free_double_array((*src)->arg);
	free(*src);
	printf("merging nodes\n");
	return (true);
}
