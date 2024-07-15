/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 05:56:40 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/15 06:04:33 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	main(int ac, char **av, char **env)
{
	t_list	pipex;
	int		state;

	if (ac < 4)
		args_error(av);
	initialize_struct(&pipex, ac, av, env);
	if (ac == 4)
		(1) && (single_command(pipex, av, env), waitpid(pipex.pid, &state, 0),
			close_infile_outfile(&pipex), exit(WEXITSTATUS(state)), 0);
	else
	{
		creat_pipes(&pipex);
		while (pipex.idx < pipex.pipe_num)
		{
			child(pipex, av, env);
			increment(&pipex);
		}
		close_pipes(&pipex);
		while (waitpid(pipex.pid, &state, 0) != -1)
			;
		close_infile_outfile(&pipex);
		exit(WEXITSTATUS(state));
	}
	return (0);
}
