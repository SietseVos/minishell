
#include <stdio.h>
#include "minishell.h"

void	run_test(char *str)
{
	char *output;

	printf("TEST CASE: %s\n", str);
	output = lexer(str);
	if (output)
	{
		printf("OUTPUT: %s\n", output);
		free(output);
	}
	printf("\n");
}

int main()
{
	run_test("this is a test without \"|mistakes<<\"");
	run_test("this is a>test>><> with|||| multiple \"|mistakes<<\"");
	run_test("this is |<<<< an incorrect string");
	run_test("this is || an incorrect string");
	run_test("this is ||| | an incorrect string");
	run_test("this is || | an incorrect string");



	run_test("|jkjgjvcklxmvklcx");
	run_test("||jkjgjvcklxmvklcx");
	run_test("||| test > out | cat -e");
	run_test("| test > out | cat -e");
	return (0);
}

// gcc lexer_tester.c lexer.c in_string.c check_syntax_error.c -I ../../include/ -I ../../src/libft ../../src/libft/libft.a -fsanitize=address -g