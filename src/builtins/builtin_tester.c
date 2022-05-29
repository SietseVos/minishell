
#include "minishell.h"

void	print_pwd_nodes(env_vars_t *list)
{
	env_vars_t	*tmp;

	tmp = get_variable_node(list, "PWD=");
	if (tmp)
		printf("%s\n", tmp->str);
	else
		printf("No PWD node!\n");
	tmp = get_variable_node(list, "OLDPWD=");
	if (tmp)
		printf("%s\n\n", tmp->str);
	else
		printf("No OLDPWD node!\n");
}

void	print_env_list(env_vars_t *list)
{
	printf("----------------	START OF LIST	----------------\n\n");
	while (list)
	{
		printf("%s\n", list->str);
		list = list->next;
	}
	printf("\n-----------------	END OF LIST	-----------------\n\n");
}

void	run_test_cd(char **arg, env_vars_t *list)
{
	char		*dir_check;
	env_vars_t	*PATH;

	printf("command %s\n", arg[0]);
	dir_check = getcwd(NULL, 0);
	PATH = get_variable_node(list, "PWD=");
	if (PATH)
		printf("Before cd working dir = %s\nIn list = %s\n\n", dir_check, PATH->str);
	printf("exit value before: %d\nCalling cd %s\n", g_exit_status, arg[0]);
	cd(arg, list);
	printf("exit value after: %d\n", g_exit_status);
	free(dir_check);
	dir_check = getcwd(NULL, 0);
	PATH = get_variable_node(list, "PWD=");
	if (PATH)
		printf("\nAfter cd working dir = %s\nIn list = %s\n", dir_check, PATH->str);
	free(dir_check);
	printf("\n");
}

void	run_test_pwd(char **arg)
{
	printf("exit value: %d\n", g_exit_status);
	pwd();
	printf("exit value: %d\n", g_exit_status);
}

void	run_unset(char **arg, env_vars_t *list)
{
	printf("exit value: %d\n", g_exit_status);
	unset(arg, &list);
	printf("exit value: %d\n", g_exit_status);
	// print_env_list(list);
}

int32_t main(int argc, char **argv, char **envp)
{
	env_vars_t 	*list;
	char 		*arg0[] = {NULL, NULL};
	char 		*arg1[] = {"..", NULL};
	char 		*arg2[] = {"../../../test", NULL};
	char 		*arg3[] = {"this is a wrong input!", NULL};
	char 		*arg4[] = {"test", "test2", "test3", NULL};
	char 		*arg5[] = {"PATH", "VSCODE", "PWD", NULL};
	char 		*arg6[] = {"PWD", NULL};

	create_env_vars_list(envp, &list);
	export(arg0, list);
	// print_pwd_nodes(list);
	// print_env_list(list);
	// printf("PWD unset\n");
	// run_unset(arg6, list);
	// print_pwd_nodes(list);
	// print_env_list(list);
	// printf("PWD cd ..\n");
	// run_test_cd(arg1, list);
	// print_pwd_nodes(list);
	// print_env_list(list);
	// printf("PWD cd ..\n");
	// run_test_cd(arg1, list);
	// print_pwd_nodes(list);
	// run_test_cd(arg1, list);
	// print_pwd_nodes(list);
	// print_env_list(list);
	// printf("----------------- cd Tests -----------------\n");
	// printf("---------------- test 01: %s ---------------\n", arg1[0]);
	// run_test_cd(arg1, list);
	// printf("---------------- test 02: %s ---------------\n", arg2[0]);
	// run_test_cd(arg2, list);
	// printf("---------------- test 03: %s ---------------\n", arg3[0]);
	// run_test_cd(arg3, list);
	// printf("-----------------   ----   -----------------\n\n");
	// printf("----------------- pwd Test -----------------\n");
	// run_test_pwd(arg2);
	// printf("-----------------   ----   -----------------\n\n");
	// printf("----------------- unset Test -----------------\n");
	// run_unset(arg4, list);
	// run_unset(arg5, list);
	// printf("-----------------   ----   -----------------\n\n");
	// system("leaks a.out");
	return (0);
}

//	unset PWD, then CD then check env list for PWD and OLDPWD

// empty lines should not be added to the history (up arrow)

// gcc unset.c echo.c cd.c exit.c export.c pwd.c strings_in_array.c builtin_tester.c ../env_functions/add_env_node.c ../env_functions/create_env_vars_list.c ../env_functions/env_list_to_array.c ../env_functions/get_variable_node.c -I ../../include/ -I ../../src/libft ../../src/libft/libft.a -fsanitize=address -g