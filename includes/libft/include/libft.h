/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:32:34 by 0xNino            #+#    #+#             */
/*   Updated: 2022/05/06 03:19:05 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <sys/types.h> 
# include <sys/stat.h> 
# include <fcntl.h>
# include <limits.h>

# define FT_INT_MIN			(-2147483648)
# define FT_INT_MAX			(2147483647)
# define FT_LONG_MIN		(-9223372036854775808)
# define FT_LONG_MAX		(9223372036854775807)
# define FT_ULONG_MAX		(18446744073709551615)
# define FT_HEX_LOWER		"0123456789abcdef"
# define FT_HEX_UPPER		"0123456789ABCDEF"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_node
{
	struct s_node	*prev;
	void			*content;
	struct s_node	*next;
}	t_node;

typedef struct s_dlist
{
	size_t	size;
	t_node	*first;
	t_node	*last;
}	t_dlist;

// additional
long	ft_atol(const char *str);
int		ft_isnumber(char *str);
char	*ft_itoa(int n);
int		ft_matrix_isnumber(char **matrix);
char	**ft_matrixtrim_free(char **matrix, char *set);
void	ft_putchar_fd(char c, int fd);
void	ft_putchar(char c);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_base(int nbr, char *base);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr(char *s);
char	**ft_split(char const *s, char c);
int		ft_strchr_pos(const char *s, const char *set);
char	*ft_strchr_set(const char *str, const char *set);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin_variadic(unsigned int arg_count, ...);
char	*ft_strjoin_variadic2(unsigned int arg_count, ...);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strrchr_pos(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strtrim_free(char *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_unique(char *str, char c);
// dlst
t_dlist	*ft_dlstadd_first(t_dlist *dlst, void *content);
t_dlist	*ft_dlstadd_last(t_dlist *dlst, void *content);
void	ft_dlstclear(t_dlist **dlst);
void	*ft_dlstcontent(t_dlist *dlst, size_t i);
t_dlist	*ft_dlstnew(void);
t_node	*ft_dlstpush_first(t_dlist *dlst);
t_node	*ft_dlstpush_last(t_dlist *dlst);
t_dlist	*ft_dlstput_last(t_dlist *dlst, t_node *node);
t_dlist	*ft_dlstput_first(t_dlist *dlst, t_node *node);
void	ft_dlstprintint(t_dlist *dlst, char *name);
int		ft_dlstisordered(t_dlist *dlst, int (*f)(t_node *, t_node *));
t_dlist	*ft_dlststcpy(t_dlist *dlst, void *(*f)(void *));
void	ft_dlstunlink(t_node *node, t_dlist *dlst);

// gnl
char	*get_next_line(int fd);
char	*ft_read_reminder(int fd, char *reminder);
char	*ft_get_line(char *reminder);
char	*ft_new_reminder(char *reminder);
char	*ft_strjoin_gnl(char *reminder, char *buf);

// libc
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
char	*ft_strndup(char *s, int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

// lst
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

// math
int		ft_abs(int a);
int		ft_max(int a, int b);
int		ft_min(int a, int b);

// printf
int		ft_hexlen(unsigned long n);
char	ft_htoc(unsigned long n, char specifier);
char	*ft_itoh(char *hex, int len, unsigned long n, char specifier);
int		ft_printf(const char *format, ...);
int		ft_putchar_len(int c);
int		ft_puthex_len(unsigned long n, int specifier);
int		ft_putnbr_len(int n, char specifier);
int		ft_putstr_len(char *s);

// sort
void	ft_quicksort(int *arr, int start, int end);

// utils
int		*ft_argv_to_i_arr(int argc, char **argv);
void	ft_free_double_ptr(void ***ptr);
void	ft_free_matrix(char ***matrix);
void	ft_free_ptr(void **ptr);
void	ft_free_variadic(unsigned int arg_count, ...);
int		ft_intlen(int n);
void	ft_loop(void);
char	**ft_matrixcat(char **matrix, char *str);
char	**ft_matrixdup(char **matrix);
size_t	ft_matrixlen(char **matrix);
void	ft_matrixprint(char **matrix, int len, int fd);
void	ft_swap_int(int *a, int *b);
int		ft_uintlen(unsigned int n);
void	ft_print_i_arr(int *i_arr, int size, char *name);

#endif
