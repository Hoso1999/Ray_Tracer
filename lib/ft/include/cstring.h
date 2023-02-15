#ifndef CSTRING_H
#define CSTRING_H




# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "ctypes.h"






void				ft_putchar(char c);

void				ft_putchar_fd(char c, int fd);

void				ft_putstr(char *s);

void				ft_putstr_fd(char *s, int fd);

void				ft_putendl(char *s);

void				ft_putendl_fd(char *s, int fd);

void				ft_putnbr(int n);

void				ft_putnbr_fd(int n, int fd);

void				*ft_memset(void *b, int c, size_t len);

void				ft_memdel(void **mem);

void				ft_bzero(void *s, size_t n);

void				*ft_memcpy(void *dst, const void *src, size_t n);

void				*ft_memccpy(void *dst, const void *src, int c, size_t n);

void				*ft_memchr(const void *s, int c, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				*ft_memmove(void *dst, const void *src, size_t len);

void				ft_strdel(char **str);

bool				ft_strequ(char const *str1, char const *str2);

int					ft_atoi_error(const char *str);

char				**ft_strsplit(char const *s, char c);

int					ft_atoi(const char *str);

size_t				ft_strlen(const char *str);

char				*ft_strcat(char *dest, const char *src);

char				*ft_strncat(char *s1, const char *s2, size_t n);

size_t				ft_strlcat(char *dst, const char *src, size_t size);

int					ft_strcmp(const char *str1, const char *str2);

int					ft_strncmp(const char *str1, const char *str2, size_t n);

char				*ft_strcpy(char *dest, const char *src);

char				*ft_strncpy(char *dst, const char *src, size_t len);

size_t				ft_strlcpy(char *st, const char *src, size_t dstsize);

char				*ft_strstr(const char *haystack, const char *needle);

char				*ft_strnstr(const char *haystack, const char *needle, size_t len);

char				*ft_strdup(const char *s1);

char				*ft_strchr(const char *s, int c);

char				*ft_strrchr(const char *s, int c);

char				*ft_vecstr_search(char **vecstr, char *search);

void				ft_vecstrdel(char ***vecstr);

char				*ft_strrev(char *str);

char				*ft_strjoin(char const *s1, char const *s2);

char				**ft_split(char const *s, char c);

char				*ft_itoa(int n);

char				*ft_substr(char const *s, unsigned int start, size_t len);

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char				*ft_strtrim(char const *s1, char const *set);

char				*ft_strnew(size_t size);


























#endif
