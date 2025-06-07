//split.c

#include "pipex.h"

char **split_args(const char *cmdline) {
	int argc;
    char **argv;
    const char *p;
	char *arg;
	
	argc = 0;
	argv = (char **)malloc(BUFFER_SIZE * sizeof(char *));
	p = cmdline;
	p = skip_spaces(p);
    while (*p)
	{
        if (!*p)
			break;
		arg = copy_arg(&p);
        add_arg(&argv, &argc, arg);
		p = skip_spaces(p);
    }
    argv[argc] = NULL;
    return (argv);
}

void free_split_args(char **args)
{
    int i = 0;
    if (!args)
        return;
    while (args[i])
        free(args[i++]);
    free(args);
}