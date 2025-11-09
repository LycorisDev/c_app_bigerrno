#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_atoi(const char *n);
int		ft_atoi_base(const char *n, const char *base);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
float	ft_clamp(float n, float min, float max);
char	*ft_gnl(int fd);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_islower(int c);
int		ft_isspace(int c);
int		ft_isupper(int c);
char	*ft_itoa(int n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
long	ft_pow(const int factor, int exponent);
int		ft_printf(const char *format, ...);
ssize_t	ft_putstr(int fd, const char *s);
char	**ft_split(const char *s, char c);
int		ft_strcasecmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strchrnul(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strncasecmp(const char *s1, const char *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_toupper(int c);
char	*ft_uitoa(unsigned int n);
char	*ft_uitoa_base(unsigned int n, char *base);
char	*ft_ultoa_base(unsigned long n, char *base);

typedef struct s_list
{
	void			*data;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

size_t	ft_list_size(t_list *list);
t_list	*ft_list_find_at(t_list *list, size_t index);
t_list	*ft_list_find_if(t_list *list, int (*f)(void *));
t_list	*ft_list_last(t_list *list);
t_list	*ft_list_new(void *data);
void	ft_list_add_front(t_list *list, t_list *new);
void	ft_list_add_back(t_list *list, t_list *new);
int		ft_list_add_sorted(t_list *list, t_list *new, int (*f)(void *, void *));
int		ft_list_is_sorted(t_list *list, int (*f)(void *, void *));
void	ft_list_swap_data(t_list *a, t_list *b);
void	ft_list_sort(t_list *list, int (*f)(void *, void *));
void	ft_list_del_one(t_list *node, void (*del)(void *));
void	ft_list_del_if(t_list *list, int (*f)(void *), void (*del)(void *));
void	ft_list_clear(t_list *list, void (*del)(void *));
int		ft_list_any(t_list *list, int (*f)(void *));
size_t	ft_list_count_if(t_list *list, int (*f)(void *));
void	ft_list_iter(t_list *list, void (*f)(void *));
t_list	*ft_list_map(t_list *list, void *(*f)(void *), void (*del)(void *));

#endif
