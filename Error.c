/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 05:56:43 by mkimdil           #+#    #+#             */
/*   Updated: 2024/08/10 00:47:40 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_strlen(char *str)
{
	if (*str == '\0')
		return (0);
	return (1 + ft_strlen(str + 1));
}

void	putchar_fd(int fd, char c)
{
	if (fd < 0)
		return ;
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
