#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <ctype.h>
#include "libft.h"

int main()
{
	printf("\n\n#############################################\n\nmain\n\n#################################################\n\n");
    /* ft_isalpha */
    char string;
    string = '4';
    printf("ft_isalpha:\n%d", ft_isalpha(string));
	printf("\nisalpha:\n%d", isalpha(string));

    /* ft_isdigit */
    char string1;
    string1 = '1';
    printf("\n\nft_isdigit:\n%d", ft_isdigit(string1));
	printf("\nisdigit:\n%d", isdigit(string1));

    /* ft_isalnum */
    char string2;
    string2 = '1';
    printf("\n\nft_isalnum:\n%d", ft_isalnum(string2));
	printf("\nisalnum:\n%d", isalnum(string2));

    /* ft_isascii*/
    int p;
    p = 5;
    printf("\n\nft_isascii:\n%d", ft_isascii(p));
	printf("\nisascii:\n%d", isascii(p));

    /* ft_isprint */
    char string3;
    string3 = '1';
    printf("\n\nft_isprint:\n%d", ft_isprint(string3));
	printf("\nisprint:\n%d", isprint(string3));

    /* ft_strlen */
    char *string4 = "12345678jrkrjg90";
    printf("\n\nft_strlen:\n%lu", ft_strlen(string4));
	printf("\nstrlen:\n%lu", strlen(string4));

    /* ft_memset */
    char string5[19] = "12345678jrkrjg90";
	char teststring5[] = "12345678jrkrjg90";
	ft_memset(string5, 'g', 9);
	memset(teststring5, 'g', 9);
    printf("\n\nft_memset:\n%s", string5);
	printf("\nmemset:\n%s", teststring5);

    /* ft_bzero */
    char string6[19] = "ooijhhyu4567";
	char teststring6[19] = "ooijhhyu4567";
	ft_bzero(string6, 9);
	bzero(teststring6, 9);
    printf("\n\nft_bzero:\n%s", string6);
	printf("\nbzero:\n%s", teststring6);

    /* ft_memcpy */
    char string7[15] = "ooijhhyu45";
	char string8[20] = "testes";
	char teststring7[15] = "ooijhhyu45";
	char teststring8[20] = "testes";
    printf("\n\nft_memcpy:\n%s", (char *)ft_memcpy(((void *)0), ((void *)0), 11));
	printf("\nmemcpy:\n%s", (char *)memcpy(((void *)0), ((void *)0), 11));

    /* ft_memmove */
    char string9[] = "ooijhhyu45";
	char teststring9[] = "ooijhhyu45";
	ft_memmove(string9, string9 + 3, 4);
	memmove(teststring9, teststring9 + 3, 4);
    printf("\n\nft_memmove:\n%s", string9);
	printf("\nmemmove:\n%s", teststring9);

    /* ft_strlcpy */
    char string11[] = "alalall";
	char string12[20] = "testesesetstesteses";
	char teststring11[] = "alalall";
	char teststring12[30] = "testesesetstesteses";
	ft_strlcpy(string11, string12, 0);
	strlcpy(teststring11, teststring12, 0);
    printf("\n\nft_strlcpy:\n%s", string11);
	printf("\nstrlcpy:\n%s", teststring11);

    /* ft_strlcat */
    char string13[] = "there is no stars in the sky";
	char string14[] = "thx to ntoniolo for this test !";
	char teststring13[] = "there is no stars in the sky";
	char teststring14[] = "thx to ntoniolo for this test !";
	printf("\n\n%lu\n\n", ft_strlcat(string13, string14, 5));
	printf("\n\n%lu\n\n", strlcat(teststring13, teststring14, 5));
    printf("\n\nft_strlcat:\n%s", string13);
	printf("\nstrlcat:\n%s", teststring13);

	/* ft_toupper */
	char a;
	a = 'f';
	printf("\n\nft_toupper:\n%d", ft_toupper(a));
	printf("\ntoupper:\n%d", toupper(a));

	/* ft_tolower */
	char b;
	b = 'B';
	printf("\n\nft_tolower:\n%d", ft_tolower(b));
	printf("\ntolower:\n%d", tolower(b));

	/* ft_strchr */
	char *c = "abbbbbbbb";
	printf("\n\nft_strchr:\n%s", ft_strchr(c, 'b'));
	printf("\nstrchr:\n%s", strchr(c, 'b'));

	/* ft_strrchr */
	char d[15] = "woepdaloep";
	printf("\n\nft_strrchr:\n%s", ft_strrchr(d, 'k'));
	printf("\nstrrchr:\n%s", strrchr(d, 'k'));

	/* ft_strncmp */
	printf("\n\nft_strncmp:\n%d", ft_strncmp("test", "test ", 5));
	printf("\nstrncmp:\n%d", strncmp("test", "test ", 5));

	/* ft_memchr */
	char e[15] = "woepdaloep";
	printf("\n\nft_memchr:\n%s", ft_memchr(e, 'd', 10));
	printf("\nmemchr:\n%s", memchr(e, 'd', 10));

	/* ft_memcmp */
	char f[] = "\xff\0\0\xaa\0\xde\xffMACOSX\xff";
	char g[] = "\xff\0\0\xaa\0\xde\x00MBS";
	printf("\n\nft_memcmp:\n%d", ft_memcmp(f, g, 8));
	printf("\nmemcmp:\n%d", memcmp(f, g, 8));

	/* ft_strnstr */
	char haystack[] = "MZIRIBMZIRIBMZE123";
	char needle[] = "MZIRIBMZE";
	printf("\n\nft_strnstr:\n%s", ft_strnstr(haystack, needle, 9));
	printf("\nstrnstr:\n%s", strnstr(haystack, needle, 9));

	/* ft_atoi */
	char h[15] = "  +-546";
	printf("\n\nft_atoi:\n%d", ft_atoi(h));
	printf("\n\natoi:\n%d", atoi(h));

	/* ft_calloc */
	char	*ptr;
	char	*testptr;
	ptr = (char*)ft_calloc(0, 0);
	testptr = (char*)calloc(0, 0);
	ptr[0] = 'a';
	testptr[0] = 'a';
	printf("\n\nft_calloc:\n%s", ptr);
	printf("\ncalloc:\n%s", testptr);
	
	/* ft_strdup */
	char i[15] = "String copied.";
	char *j = ft_strdup(i);
	char *testj = strdup(i);
	printf("\n\nft_strdup:\n%s", j);
	printf("\nstrdup:\n%s", testj);

	/* ft_substr */
	char k[40] = "i just want this part #############";
	printf("\n\nft_substr:\n%s", ft_substr(k, 7, 0));

	/* ft_strjoin */
	char l[] = "crtl c ";
	char m[] = "+ v";
	printf("\n\nft_strjoin:\n%s", ft_strjoin(l, m));

	/* ft_strtrim */
	char n[] = "";
	char set[] = "? \n\t";
	printf("\n\nft_strtrim:\n%s", ft_strtrim(n, set));

	/* ft_split */
	int o;
	char	**tabstr;

	o = 0;
 	if (!(tabstr = ft_split("lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse", ' ')))
			printf("NULL");
		else
		{
			while (tabstr[o] != NULL)
			{
				printf("%s\n", tabstr[o]);
				o++;
			}
		}


	/* ft_itoa */
	int u;
	u = -100;
	printf("\n\nft_itoa:\n%s", ft_itoa(u));

	/* ft_strmapi */
	char *v = "dsfs";
	char *x;
	x = ft_strmapi(v, testfunction);
	printf("\n\nft_strmapi:\n%s", x);

	/* ft_striteri */
	char *y = "dsfg";
	ft_striteri(y, testfunction2);
	printf("\n\nft_striteri:\n%s", y);

	/* ft_putchar_fd */
	write(1, "\n\nft_putchar_fd:\n", 17);
	ft_putchar_fd('d', 1);

	/* ft_putstr_fd */
	write(1, "\n\nft_putstr_fd:\n", 17);
	ft_putstr_fd("This is a sting.", 1);

	/* ft_putendl_fd */
	write(1, "\n\nft_putendl_fd:\n", 17);
	ft_putendl_fd("This is a sting.", 1);

	/* ft_putnbr_fd */
	write(1, "\n\nft_putnbr_fd:\n", 17);
	ft_putnbr_fd(-2147483647, 1);
	write(1, "\n\n", 2);


	/* BONUS PART */
	printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\nBONUS PART:");


	/* ft_lstnew */
	t_list *list1;
	list1 = ft_lstnew(ft_strdup("testing"));
	printf("\n\nft_lstnew:\n%s", list1->content);

	/* ft_lstadd_front */
	t_list *list2;
	list2 = ft_lstnew(ft_strdup("just a string"));
	ft_lstadd_front(&list1, list2);
	printf("\n\nft_lstadd_front:");
	printlst(list2);

	/* ft_lstsize */
	printf("\n\nft_lstsize:\n%d", ft_lstsize(list2));

	/* ft_lstlast */
	t_list *point2;
	point2 = ft_lstlast(list1);
	printf("\n\nft_lstlast:\n%s", point2->content);

	/* ft_lstadd_back */
	t_list	*list3;
	list3 = ft_lstnew(ft_strdup("final string"));
	ft_lstadd_back(&list1, list3);
	printf("\n\nft_lstadd_back:");
	printlst(list1);

	/* ft_lstdelone */
	ft_lstdelone(list2, deletion_test);
	printf("\n\nft_lstdelone:");
	printlst(list3);

	/* ft_lstclear */
	//make element list4
	t_list	*list4;
	list4 = ft_lstnew(ft_strdup("vier"));
	// make element list 5
	t_list	*list5;
	list5 = ft_lstnew(ft_strdup("vijf"));
	// link everytthing to end of list 1
	ft_lstadd_back(&list3, list4);
	ft_lstadd_back(&list3, list5);
	// print
	printf("\n\nft_lstclear:\n");
	ft_lstclear(&list3, deletion_test);
	printlst(list3);
	
	/* ft_lstiter */
	// make new list
	t_list	*numbs;
	printf("\n\nft_lstiter:\n");
	numbs = newlst(4);
	ft_lstiter(numbs, testfunction3);

	/* ft_lstmap */
	t_list *reslst;
	printf("\n\nft_lstmap:\n");
	reslst = ft_lstmap(numbs, testfunction4, deletion_test);
	printlst(reslst);


}
