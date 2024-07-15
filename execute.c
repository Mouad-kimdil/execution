#include "execute.h"

int	main(int ac, char **av, char **env)
{
	t_list	pipex;
	int		state;

	if (ac < 4)
		args_error(av);	
	initialize_struct(&pipex, ac, av, env);
	if (ac == 4)
	{
		single_command(pipex, av, env);
		waitpid(pipex.pid, &state, 0);
		close_infile_outfile(&pipex);
		exit(WEXITSTATUS(state));
	}
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
