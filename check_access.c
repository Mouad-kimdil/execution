/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 05:56:53 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/15 05:57:26 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*get_path(char **env)
{
	int		i;

	if (env == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
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
