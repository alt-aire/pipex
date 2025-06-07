//pipex.h

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_pipe
{
    int     file;
    int     fd;
    char    **cmd;
    pid_t   pid;
} t_pipe;

typedef struct s_pipex
{
    t_pipe inpipe;
    t_pipe outpipe;
    int    pipe_fd[2];
    char  **path;
} t_pipex;

void execute_command(char *cmd, char **envp);
void process(t_pipex *data, char **argv, char **envp, bool oi);
void error_exit(const char *msg);
void cleanup(t_pipex *data);

char **split_args(const char *cmdline);
void free_split_args(char **args);

const char *skip_spaces(const char *p);
char *copy_arg(const char **pp);
void add_arg(char ***argv, int *argc, char *arg);

char *find_in_path(const char *cmd, char **envp);

#endif