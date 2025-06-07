//split_utils.c
#include "pipex.h"

static bool is_end_of_arg(char c, bool in_single, bool in_double)
{
    return (!in_single && !in_double && (c == ' ' || c == '\t' || c == '\0'));
}

static char process_escape(const char **p)
{
    (*p)++;
    return (**p);
}

static void update_quotes(char c, bool *in_single, bool *in_double) {
    if (c == '\'' && !(*in_double))
        *in_single = !(*in_single);
    else if (c == '"' && !(*in_single))
        *in_double = !(*in_double);
}

char *copy_arg(const char **pp) {
    const char *p;
    bool in_single;
	bool in_double;
    char *buf;
    int len;

	p = *pp;
    in_single = false; 
	in_double = false;
    buf = (char *)malloc((ft_strlen((char *)p) + 1)*sizeof(char));
    len = 0;
    while (*p)
	{
        if (is_end_of_arg(*p, in_single, in_double))
            break ;
        if (*p == '\\' && p[1])
            buf[len++] = process_escape(&p);
        else if (*p == '\'' || *p == '"')
            update_quotes(*p, &in_single, &in_double);
        else
            buf[len++] = *p;
        p++;
    }
    buf[len] = '\0';
    *pp = p;
    return buf;
}

void add_arg(char ***argv, int *argc, char *arg)
{
    char **new_argv;
	static int buffer_size;
    int i;

	buffer_size=BUFFER_SIZE;
    if (*argc + 1 >= buffer_size)
    {
        buffer_size*=2;
        new_argv = (char **)malloc((buffer_size) * sizeof(char *));
        i = 0;
        while (i < *argc)
        {
            new_argv[i] = (*argv)[i];
            i++;
        }
        free(*argv);
        *argv = new_argv;
    }
    (*argv)[(*argc)++] = arg;
}

const char *skip_spaces(const char *p)
{
    while (*p == ' ' || *p == '\t')
        p++;
    return p;
}