/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:22:25 by mkerrien          #+#    #+#             */
/*   Updated: 2025/08/04 01:53:05 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <float.h>
# include <stdarg.h>
# include <limits.h>
# include <math.h>

# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 1
# endif

/* Colors */
# define RST "\001\033[0m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[0;33m\002"
# define BLUE "\001\033[0;34m\002"
# define MAGENTA "\001\033[0;35m\002"
# define CYAN "\001\033[0;36m\002"
# define WHITE "\001\033[0;37m\002"
# define ORANGE "\001\033[0;91m\002"
# define PURPLE "\001\033[0;95m\002"
# define DARK_ORANGE "\001\033[0;33m\002"
# define PINK "\001\033[0;95m\002"
# define TEAL "\001\033[0;96m\002"
# define GRAY "\001\033[0;90m\002"

/* Styles */
# define BOLD      "\001\033[1m\002"
# define ITALIC    "\001\033[3m\002"
# define UNDERLINE "\001\033[4m\002"


/* Bold Colors */
# define BOLD_BLACK "\033[1;30m"
# define BOLD_GREEN "\033[1;32m"
# define BOLD_RED "\033[1;31m"
# define BOLD_YELLOW "\033[1;33m"
# define BOLD_BLUE "\033[1;34m"
# define BOLD_CYAN "\033[1;36m"
# define BOLD_PURPLE "\033[1;35m"
# define BOLD_WHITE "\033[1;37m"

/* Underline */
# define U_BLACK "\033[4;30m"
# define U_RED "\033[4;31m"
# define U_GREEN "\033[4;32m"
# define U_YELLOW "\033[4;33m"
# define U_BLUE "\033[4;34m"
# define U_PURPLE "\033[4;35m"
# define U_CYAN "\033[4;36m"
# define U_WHITE "\033[4;37m"

/* Background */
# define ON_BLACK "\033[40m"
# define ON_RED "\033[41m"
# define ON_GREEN "\033[42m"
# define ON_YELLOW "\033[43m"
# define ON_BLUE "\033[44m"
# define ON_PURPLE "\033[45m"
# define ON_CYAN "\033[46m"
# define ON_WHITE "\033[47m"

/* High Intensty */
# define I_BLACK "\033[0;90m"
# define I_RED "\033[0;91m"
# define I_GREEN "\033[0;92m"
# define I_YELLOW "\033[0;93m"
# define I_BLUE "\033[0;94m"
# define I_PURPLE "\033[0;95m"
# define I_CYAN "\033[0;96m"
# define I_WHITE "\033[0;97m"

/* Bold High Intensty */
# define BI_BLACK "\033[1;90m"
# define BI_RED "\033[1;91m"
# define BI_GREEN "\033[1;92m"
# define BI_YELLOW "\033[1;93m"
# define BI_BLUE "\033[1;94m"
# define BI_PURPLE "\033[1;95m"
# define BI_CYAN "\033[1;96m"
# define BI_WHITE "\033[1;97m"

/* High Intensty backgrounds */
# define ON_I_BLACK "\033[0;100m"
# define ON_I_RED "\033[0;101m"
# define ON_I_GREEN "\033[0;102m"
# define ON_I_YELLOW "\033[0;103m"
# define ON_I_BLUE "\033[0;104m"
# define ON_I_PURPLE "\033[10;95m"
# define ON_I_CYAN "\033[0;106m"
# define ON_I_WHITE "\033[0;107m"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);

int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_atoi(const char	*nptr);
char			*ft_itoa(int n);
char			*ft_ltoa(long long n);
char			*ft_dtoa(double n, int precision);
double			ft_atod(const char *str);

int				ft_strcmp(char *s1, char *s2);
int				ft_strcmp_safe(const char *s1, const char *s2, int *cmp_result);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strncmp_safe(const char *s1, const char *s2, size_t n, \
		int *cmp_result);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t siz);
size_t			ft_strlcat(char *dst, const char *src, size_t siz);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strdup(const char *s);
char			**ft_strsdup(const char **tab);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strfjoin(char *s1, char *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_first_l_in_up(char *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_str_toupper(char *s);
void			ft_str_tolower(char *s);
void			ft_free_fullstrs(char ***tab);
void			ft_free_strs(char **tab);

int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
void			ft_fcalloc(size_t nmemb, size_t size, void **ptr);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			**ft_split(char const *s, char c);

int				ft_putchar(char c);
int				ft_putstr(char *str);
int				ft_putnbr(int nb);
int				ft_putunbr(unsigned int nb);
int				ft_puthex(unsigned long nbr, const int upper);
int				ft_putptr(void *ptr);

int				ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char *s, int fd);
int				ft_putnbr_fd(int n, int fd);
int				ft_putunbr_fd(unsigned int nb, int fd);
int				ft_puthex_fd(unsigned long nbr, const int isupper, int fd);
int				ft_putptr_fd(void *ptr, int fd);
void			ft_putendl_fd(char *s, int fd);

int				ft_printf(const char *format, ...);
int				ft_printf_fd(int fd, const char *format, ...);
char			*get_next_line(int fd, int end);

int				ft_check_int_overflow(char *s);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
		void (*del)(void *));

#endif
