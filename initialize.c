/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 05:56:36 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/15 06:04:46 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	dup_files(int infile, int outfile)
{
	int	errnum;

	if (dup2(infile, 0) < 0)
	{
		errnum = errno;
		putstr_fd(2, strerror(errnum));
		exit(EXIT_FAILURE);
	}
	if (dup2(outfile, 1) < 0)
	{
		errnum = errno;
		putstr_fd(2, strerror(errnum));
		exit(EXIT_FAILURE);
	}
}
