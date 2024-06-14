#include "execute.h"

void	child(t_list pipex, char **av, char **env)
{
	int	errnum;

	pipex.pid = fork();
	if (pipex.pid < 0)
	{
		errnum = errno;
		putstr_fd(2, strerror(errnum));
		exit(EXIT_FAILURE);
	}
	if (pipex.pid == 0)
	{
		if (pipex.idx == 0)
			dup_files(pipex.infile, pipex.fds[0][1]);
		else if (pipex.idx == pipex.pipe_num - 1)
		{
			if (pipex.pipe_num == 2)
				dup_files(pipex.fds[0][0], pipex.outfile);
			else
				dup_files(pipex.fds[pipex.d_idx - 1][0], pipex.outfile);
		}
		else
			dup_files(pipex.fds[pipex.d_idx - 1][0], pipex.fds[pipex.d_idx][1]);
		close_pipes(&pipex);
		pipex.cmd = ft_split(av[pipex.c_idx], ' ');
		if (!pipex.cmd)
			cmd_error(&pipex);
		pipex.cmd_path = get_cmd_path(pipex);
		if (execve(pipex.cmd_path, pipex.cmd, env) < 0)
		{
			errnum = errno;
			putstr_fd(2, strerror(errnum));
			exit(EXIT_FAILURE);
		}
	}
}
