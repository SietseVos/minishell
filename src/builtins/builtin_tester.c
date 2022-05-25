
#include "minishell.h"

void	print_env_list(env_vars_t *list)
{
	printf("----------------	START OF LIST	----------------\n\n");
	while (list)
	{
		printf("%s\n", list->str);
		list = list->next;
	}
	printf("-----------------	END OF LIST	-----------------\n\n");
}

void	run_test_cd(char **arg, env_vars_t *list)
{
	char		*dir_check;
	env_vars_t	*PATH;

	dir_check = getcwd(NULL, 0);
	PATH = get_variable_node(list, "PWD=");
	printf("Before cd working dir = %s\nIn list = %s\n\n", dir_check, PATH->str);
	printf("exit value: %d\n", g_exit_status);
	cd(arg, list);
	printf("exit value: %d\n", g_exit_status);
	free(dir_check);
	dir_check = getcwd(NULL, 0);
	PATH = get_variable_node(list, "PWD=");
	printf("\nAfter cd working dir = %s\nIn list = %s\n", dir_check, PATH->str);
	free(dir_check);
	printf("\n");
}

void	run_test_pwd(char **arg)
{
	printf("exit value: %d\n", g_exit_status);
	pwd(arg);
	printf("exit value: %d\n", g_exit_status);
}

void	run_unset(char **arg, env_vars_t *list)
{
	printf("exit value: %d\n", g_exit_status);
	unset(arg, &list);
	printf("exit value: %d\n", g_exit_status);
	print_env_list(list);
}

int32_t main(int argc, char **argv, char **envp)
{
	env_vars_t 	*list;
	char 		*arg1[] = {"..", NULL};
	char 		*arg2[] = {"../../../test", NULL};
	char 		*arg3[] = {"this is a wrong input!", NULL};
	char 		*arg4[] = {"test", "test2", "test3", NULL};
	char 		*arg5[] = {"PATH", "VSCODE", "PWD", NULL};

	create_env_vars_list(envp, &list);
	print_env_list(list);
	printf("----------------- cd Tests -----------------\n");
	printf("---------------- test 01: %s ---------------\n", arg1[0]);
	run_test_cd(arg1, list);
	printf("---------------- test 02: %s ---------------\n", arg2[0]);
	run_test_cd(arg2, list);
	printf("---------------- test 03: %s ---------------\n", arg3[0]);
	run_test_cd(arg3, list);
	printf("-----------------   ----   -----------------\n\n");
	printf("----------------- pwd Test -----------------\n");
	run_test_pwd(arg2);
	printf("-----------------   ----   -----------------\n\n");
	printf("----------------- unset Test -----------------\n");
	run_unset(arg4, list);
	run_unset(arg5, list);
	printf("-----------------   ----   -----------------\n\n");
	return (0);
}

//	unset PWD, then CD then check env list for PWD and OLDPWD
//	check PWD and OLDPWD at startup, should be set?
//



// gcc unset.c cd.c exit.c pwd.c strings_in_array.c builtin_tester.c ../env_functions/add_env_node.c ../env_functions/create_env_vars_list.c ../env_functions/env_list_to_array.c ../env_functions/get_variable_node.c -I ../../include/ -I ../../src/libft ../../src/libft/libft.a -fsanitize=address -g