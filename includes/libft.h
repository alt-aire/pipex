#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>

size_t ft_strlen(char *str);
char *ft_strdup(const char *src);
char *ft_strtok(char *str, const char delim);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strchr(const char *s, int c);

#endif