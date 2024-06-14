#include "execute.h"

int	main(int ac, char **av, char **env)
{
	t_list	pipex;
	int		state;

	if (ac < 5)
		args_error(av);
	initialize_struct(&pipex, ac, av, env);
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
