/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# define GNL_BUFF_SIZE 60
# define FTS_BUFF_SIZE 1000
# define GNL_FILE_NB 128

# define TRUE			1
# define FALSE			0
# define MAX_INT		2147483647
# define MIN_INT		-2147483648

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

int					get_root(char *root, int size);
void				add_to_list(t_list **list, void *new_v, size_t size);
void				ft_arraydel(char **arr);
char				**ft_arrjoin(char **to_this, char **from_this);
int					ft_arrlen(char **arr);
double				ft_atof(const char *str);
double				ft_atof(const char *str);
int					ft_atoi(const char *str);
void				ft_bzero(void *str, size_t n);
char				*ft_b_itoa(int nbr, char *buffer);
double				ft_fclamp(double x, double a, double b);
int					ft_clamp(int x, int a, int b);
t_list				*ft_dellstnode(t_list **lst, t_list *del);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
char				*ft_itoa(int nbr);
void				ft_lstadd(t_list **alst, t_list *new);
int					ft_lstadd_new(t_list **list, void *content,
						size_t content_size);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone_nonfree(t_list **lst, t_list *del);
int					ft_lstlen(t_list *lst);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				*ft_memalloc(size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);
int					ft_min(int a, int b);
int					ft_max(int a, int b);
float				ft_fmin(float a, float b);
float				ft_fmax(float a, float b);
int					ft_nbrlen(long nbr);
double				ft_pow(double n, int pow);
long double			ft_long_pow(long double n, int pow);
void				ft_putarr(char **arr);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(char const *s);
int					ft_stradd(char **dest, char *src);
void				ft_straddchar(char **str, char c);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strchr(const char *str, int c);
int					ft_strchrlen(const char *str, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strcut(char *str, int start, int end);
void				ft_strdel(char **as);
char				*ft_strdup(const char *src);
int					ft_strendswith(char const *src, char const *comp);
int					ft_strequ(char const *s1, char const *s2);
char				**stringsplit(const char *s, char c, int *nb);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoinf(char *s1, const char *s2);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strndup(const char *s1, size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
void				ft_strnrev(char *str, int len);
char				**ft_strsplit(char const *s, char c);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *str);
void				ft_swap(int *a, int *b);
void				ft_fswap(float *a, float *b);
int					ft_wordcount(const char *s, char c);
int					get_next_line(const int fd, char **line);

#endif
