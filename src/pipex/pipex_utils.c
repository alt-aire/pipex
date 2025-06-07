//pipex_utils.c
#include <stdio.h>
#include "pipex.h"

void error_exit(const char *msg)
{
	perror(msg);
    exit(1);
}

void execute_command(char *cmd, char **envp)
{
    char **args;
    char *exec_path;

	args = split_args(cmd);
    exec_path = NULL;
    if (!args || !args[0])
    {
        free_split_args(args);
        error_exit("Invalid command or empty split_args");
    }
    if (ft_strchr(args[0], '/'))
        exec_path = ft_strdup(args[0]);
    else
        exec_path = find_in_path(args[0], envp);

    if (!exec_path || execve(exec_path, args, envp) == -1)
	{
        if (exec_path)
            free(exec_path);
        free_split_args(args);
		perror("execve");
        error_exit("execve");
    }
}

void process(t_pipex *data, char **argv, char **envp, bool oi)
{
    if (oi)
    {
        dup2(data->inpipe.file, STDIN_FILENO);
        dup2(data->pipe_fd[1], STDOUT_FILENO);
    }
    else
    {
        dup2(data->pipe_fd[0], STDIN_FILENO);
        dup2(data->outpipe.file, STDOUT_FILENO);
    }
    close(data->pipe_fd[0]);
    close(data->pipe_fd[1]);
    close(data->inpipe.file);
    close(data->outpipe.file);
	if(oi)
		execute_command(argv[2], envp);
	else
		execute_command(argv[3], envp);
}

void cleanup(t_pipex *data)
{
    if (data->inpipe.file >= 0)
        close(data->inpipe.file);
    if (data->outpipe.file >= 0)
        close(data->outpipe.file);
}