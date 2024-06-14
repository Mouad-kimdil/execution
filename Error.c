#include "execute.h"

int	ft_strlen(char *str)
{
	if (*str == '\0')
		return (0);
	return (1 + ft_strlen(str + 1));
}

void	putchar_fd(int fd, char c)
{
	write (fd, &c, 1);
}

void	putnbr_fd(int fd, int nb)
{
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		putnbr_fd(fd, nb / 10);
		putchar_fd(fd, (nb % 10) + 48);
	}
	else
		putchar_fd(fd, nb + 48);
}

void	putstr_fd(int fd, char *str)
{
	write (fd, str, ft_strlen(str));	
}

void	print_args(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		putstr_fd(2, av[i]);
		if (av[i + 1])
			putchar_fd(2, ' ');
		i++;
	}
	putchar_fd(2, '\n');
}

void	free_struct(t_list *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->pipe_num)
	{
		free(pipex->fds[i]);
		i++;
	}
	free(pipex->fds);
}

void	cmd_error(t_list *pipex)
{
	free_struct(pipex);
	exit(EXIT_FAILURE);
}

void	args_error(char **av)
{
	putstr_fd(2, "not enough arguments!!\n");
	putstr_fd(2, "arguments you give: ");
	print_args(av);
	putstr_fd(2, "example: ./execute infile cmd1 cmd2 ... cmd_n outfile\n");
	exit(EXIT_FAILURE);
}
