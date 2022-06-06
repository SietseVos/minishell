
#include "minishell.h"

int32_t	chdir_error(char *str)
{
	g_exit_status = 1;
	printf("bash: cd: %s: No such file or directory\n", str);
	return (1);
}

/*
	*	This function copies the string inside pwd_node, adds "OLD" in front and then places
	*	it inside of oldpwd_node. 
	*	@param *oldpwd_node Pointer to the node where the string has the be placed.
	*	@param *pwd_node Pointer to the node containing the string that has to be copied.
	*	@param *has_been_null Pointer to a boolian that will be changed indicating it has not been set to null.
	*	@return [-1] If memory allocation fails else [0].
*/
int32_t	move_pwd_to_oldpwd(env_vars_t *oldpwd_node, env_vars_t *pwd_node, bool *has_been_null)
{
	int32_t	oldpwd_size;

	*has_been_null = false;
	free(oldpwd_node->str);
	oldpwd_node->str = NULL;
	oldpwd_size = strlen(pwd_node->str) + old + null;
	oldpwd_node->str = ft_calloc(oldpwd_size, sizeof(char));
	if (!oldpwd_node->str)
		return (-1);
	ft_strlcat(oldpwd_node->str, "OLD", oldpwd_size);
	ft_strlcat(oldpwd_node->str, pwd_node->str, oldpwd_size);
	return (0);
}

int32_t	set_oldpwd(env_vars_t *oldpwd_node)
{
	char	*cwd;

	free(oldpwd_node->str);
	oldpwd_node->str = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	oldpwd_node->str = create_new_cd_str("OLDPWD=", cwd);
	free(cwd);
	if (!oldpwd_node->str)
		return (-1);
	return (0);
}

int32_t	create_empty_oldpwd(env_vars_t *oldpwd_node, bool *has_been_null)
{
	free(oldpwd_node->str);
	oldpwd_node->str = create_new_cd_str("OLDPWD=", NULL);
	oldpwd_node->has_value = true;
	*has_been_null = true;
	if (!oldpwd_node->str)
		return (-1);
	return (0);
}