//main.c

/*
	O_WRONLY: abrir solo para escritura
	O_CREAT: si el archivo no existe, lo crea
	O_TRUNC: si el archivo ya existe, su contenido se trunca a longitud 0 (se borra lo anterior
	6: permisos de lectura y escritura para el propietario (rw-)
	4: permisos de solo lectura para el grupo (r--)
	4: permisos de solo lectura para otros (r--)
*/

#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex data;

    if (argc == 5)
	{
		data.inpipe.file = open(argv[1], O_RDONLY);
		if (data.inpipe.file < 0)
			error_exit("Error opening input file");
		data.outpipe.file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data.outpipe.file < 0)
			error_exit("Error opening output file");
		if (pipe(data.pipe_fd) < 0)
			error_exit("Pipe error");
		data.inpipe.pid = fork();
		if (data.inpipe.pid < 0)
			error_exit("Fork error");
		if (data.inpipe.pid == 0)
			process(&data, argv, envp, 1);
		data.outpipe.pid = fork();
		if (data.outpipe.pid < 0)
			error_exit("Fork error");
		if (data.outpipe.pid == 0)
			process(&data, argv, envp, 0);
		close(data.pipe_fd[0]);
		close(data.pipe_fd[1]);
		waitpid(data.inpipe.pid, NULL, 0);
		waitpid(data.outpipe.pid, NULL, 0);
		cleanup(&data);
		return (0);
	}
	return (1);
}