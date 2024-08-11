/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 05:54:33 by mkimdil           #+#    #+#             */
/*   Updated: 2024/08/10 00:58:48 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void free_arr(int **fds)
{
    int i = 0;

    if (fds == NULL)
        return;

    while (fds[i] != NULL)
    {
        free(fds[i]);
        fds[i] = NULL;
        i++;
    }
    free(fds);
    fds = NULL;
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
	if (!splited)
		return (NULL);
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
	if (!pipex->fds)
		return ;
	pipex->idx = 0;
	pipex->d_idx = 1;
	pipex->path = get_path(env);
	if (!pipex->path)
		pipex->path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
	if (!pipex->path)
	{
		free_struct(pipex);
		free_arr(pipex->fds);
		exit(EXIT_FAILURE);
	}
}
