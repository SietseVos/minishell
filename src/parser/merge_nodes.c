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

bool	dup_strs_to_chararr(char **ret, char **arr1, char **arr2)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	j = 0;
	while (arr1[i] != NULL)
	{
		ret[i] = ft_strdup(arr1[i]);
		if (ret[i] == NULL)
			return (boolerr("dup chararr string malloc fail"));
		i++;
	}
	while (arr2[j] != NULL)
	{
		ret[i] = ft_strdup(arr2[j]);
		if (ret[i] == NULL)
			return (boolerr("dup chararr string malloc fail"));
		i++;
		j++;
	}
	ret[i] = NULL;
	return (true);
}

char	**join_chararrs(char **arr1, char **arr2)
{
	int32_t	strcount;
	char	**ret;

	strcount = count_strings(arr1) + count_strings(arr2);
	ret = malloc(sizeof(char *) * (strcount + 1));
	if (ret == NULL)
		return (nullerr("failed to malloc ret for join_chararrs"));
	if (dup_strs_to_chararr(ret, arr1, arr2) == false)
	{
		free_double_array(ret);
		return (NULL);
	}
	return (ret);
}

bool	merge_nodes(action_t *dst, action_t *src, action_t **prevnextptr)
{
	char	**fragdst;
	char	**fragsrc;

	fragdst = dst->arg;
	fragsrc = src->arg;
	dst->arg = join_chararrs(fragdst, fragsrc);
	if (dst->arg == NULL)
		return (NULL);
	*prevnextptr = src->next;
	free_double_array(fragdst);
	free_double_array(fragsrc);
	free(src);
	return (true);
}
