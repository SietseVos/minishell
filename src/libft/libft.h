#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

#define uint32_t u_int32_t
#define int32_t int

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int32_t		ft_isalpha(int32_t str);
int32_t		ft_isdigit(int32_t str);
int32_t		ft_isalnum(int32_t str);
int32_t		ft_isascii(int32_t p);
int32_t		ft_isprint(int32_t str);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *str, int32_t c, size_t n);
void	ft_bzero(void *str, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int32_t		ft_toupper(int32_t a);
int32_t		ft_tolower(int32_t b);
char	*ft_strchr(const char *s, int32_t c);
char	*ft_strrchr(const char *s, int32_t c);
int32_t		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int32_t c, size_t n);
int32_t		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int32_t		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, uint32_t start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int32_t n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int32_t fd);
void	ft_putstr_fd(char *s, int32_t fd);
void	ft_putendl_fd(char *s, int32_t fd);
void	ft_putnbr_fd(int32_t n, int32_t fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int32_t		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	deletion_test(void *remove);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	printlst(t_list *print);
t_list	*newlst(int32_t len);
void	ft_lstiter(t_list *lst, void (*f)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
