//path.c
#include <unistd.h>
#include "libft.h"

static void join_path(char *dest, const char *dir, const char *cmd)
{
    size_t i;
	size_t j;

	i = 0;
	j = 0;
    while (dir[i])
	{
        dest[i] = dir[i];
		i++;
	}
	if (i > 0 && dir[i-1] != '/')
		dest[i++] = '/';
    while (cmd[j])
	{
        dest[i + j] = cmd[j];
		j++;
	}
    dest[i + j] = '\0';
}

char *find_in_path(const char *cmd, char **envp)
{
    char *path_env;
    char *paths;
    char *token;
    char *full_path;
    size_t len;
    int i;

	path_env = NULL;
    paths = NULL;
    token = NULL;
    full_path = NULL;
    i = 0;
    while (envp[i])
	{
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
            path_env = envp[i] + 5;
            break;
        }
        i++;
    }
    if (!path_env)
        return (NULL);
    paths = ft_strdup(path_env);
    if (!paths)
        return (NULL);
    token = ft_strtok(paths, ':');
    while (token)
	{
        len = ft_strlen(token) + 1 + ft_strlen((char *)cmd) + 1;
        full_path = (char *)malloc(len * sizeof(char));
        if (!full_path)
		{
            free(paths);
            return (NULL);
        }
        join_path(full_path, token, cmd);
        if (access(full_path, X_OK) == 0)
		{
            free(paths);
            return (full_path);
        }
        free(full_path);
        token = ft_strtok(NULL, ':');
    }
    free(paths);
    return (NULL);
}