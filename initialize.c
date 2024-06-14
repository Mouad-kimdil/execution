#include "execute.h"

int	get_infile(char *infile)
{
	int	fd;
	int	errnum;

	fd = open(infile, O_RDONLY, 0644);
	if (fd < 0)
	{
		errnum = errno;
		putstr_fd(2, strerror(errnum));
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	get_outfile(char *outfile)
{
	int	fd;
	int	errnum;

	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		errnum = errno;
		putstr_fd(2, strerror(errnum));
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	creat_pipes(t_list *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->pipe_num)
	{
		pipex->fds[i] = malloc(sizeof(int) * 2);
		pipe(pipex->fds[i]);
		i++;
	}
}

void	close_pipes(t_list *pipex)
{
	int	i;
	int	errnum;

	i = 0;
	while (i < pipex->pipe_num)
	{
		if (close(pipex->fds[i][0]) < 0)
		{
			errnum = errno;
			putstr_fd(2, strerror(errnum));
			exit(EXIT_FAILURE);
		}
		if (close(pipex->fds[i][1]) < 0)
		{
			errnum = errno;
			putstr_fd(2, strerror(errnum));
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	dup_files(int fd1, int fd2)
{
	int	errnum;
	if (dup2(fd1, 0) < 0)
	{
		errnum = errno;
		putstr_fd(2, strerror(errnum));
		exit(EXIT_FAILURE);
	}
	if (dup2(fd2, 1) < 0)
	{
		errnum = errno;
		putstr_fd(2, strerror(errnum));
		exit(EXIT_FAILURE);
	}
}

void	increment(t_list *pipex)
{
	pipex->c_idx++;
	pipex->idx++;
	pipex->d_idx++;
}

void	close_infile_outfile(t_list *pipex)
{
	int	errnum;

	if (close(pipex->infile) < 0)
	{
		errnum = errno;
		putstr_fd(2, strerror(errnum));
		exit(EXIT_FAILURE);
	}
	if (close(pipex->outfile) < 0)
	{
		errnum = errno;
		putstr_fd(2, strerror(errnum));
		exit(EXIT_FAILURE);
	}
}

char	*get_cmd_path(t_list pipex)
{
	char	**splited;
	char	*tmp;
	char	*temp;
	int		i;

	i = 0;
	splited = ft_split(pipex.path, ':');
	while (splited[i])
	{
		temp = ft_strjoin(splited[i], "/");
		tmp = ft_strjoin(temp, pipex.cmd[0]);
		if (access(tmp, F_OK | X_OK) == 0)
			return (free(temp), tmp);
		free(tmp);
		free(temp);
		i++;
	}
	return (NULL);
}

void	initialize_struct(t_list *pipex, int ac, char **av, char **env)
{
	pipex->infile = get_infile(av[1]);
	pipex->outfile = get_outfile(av[ac - 1]);
	pipex->pipe_num = ac - 3;
	pipex->c_idx = 2;
	pipex->pid = 0;
	pipex->fds = malloc(sizeof(int *) * pipex->pipe_num);
	pipex->idx = 0;
	pipex->d_idx = 1;
	pipex->path = get_path(env);
	if (!pipex->path)
		pipex->path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
	if (!pipex->path)
	{
		free_struct(pipex);
		exit(EXIT_FAILURE);
	}
}
