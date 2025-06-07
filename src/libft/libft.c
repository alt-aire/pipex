#include "libft.h"

size_t ft_strlen(char *str)
{
	int i;
	
	i=0;
	while(str[i])
		i++;
	return (i);
}

char *ft_strdup(const char *src)
{
    size_t len;
    char *dup;
	size_t i;

	if(!src)
		return(ft_strdup(""));
	len = ft_strlen((char *)src);
    dup = (char *)malloc((len+1)*sizeof(char));
    if (!dup)
		return (NULL);
	i = 0;
    while (i < len)
	{
        dup[i] = src[i];
		i++;
	}
	dup[i]='\0';
    return (dup);
}

char *ft_strtok(char *str, const char delim)
{
    static char *next;
    char *start;

    next = NULL;
    if (str)
        next = str;
    if (!next || !next[0])
        return (NULL);
    while (*next == delim)
        next++;
    if (!next[0])
        return (NULL);
    start = next;
    while (*next && *next != delim)
        next++;
    if (*next == delim)
    {
        *next = '\0';
        next++;
    }
    else
        next = NULL;
    return (start);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *str1;
	unsigned char *str2;
	size_t i;
	
	str1=(unsigned char *)s1;
	str2=(unsigned char *)s2;
    if (n == 0)
		return (0);
	i = 0;
    while (i < n && (s1[i] || s2[i]))
    {
        if (str1[i] != str2[i])
            return (str1[i] - str2[i]);
        i++;
    }
    return (0);
}

char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if ((char)c == '\0')
        return ((char *)s);
    return (NULL);
}