#ifndef EXECUTE_H
#define EXECUTE_H

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

typedef struct s_list
{
	int		infile;
	int		outfile;
	int		idx;
	int		d_idx;
	int		pid;
	int		pipe_num;
	int		c_idx;
	int		**fds;
	char	**cmd;
	char	*cmd_path;
	char	*path;
}	t_list;

void	putstr_fd(int fd, char *str);
void	putnbr_fd(int fd, int nb);
void	putchar_fd(int fd, char c);
int		ft_strlen(char *str);
void	args_error(char **av);
void	print_args(char **av);
void	initialize_struct(t_list *pipex, int ac, char **av, char **env);
int		get_infile(char *infile);
int		get_outfile(char *outfile);
int		countword(char *s, char c);
char	*ft_strndup(char *src, int n);
void	ft_free(char **ptr, int i);
char	**ft_help(char *s, char c, int len, char **final);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(char *s1, char *s2, int len);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *str);
char	*get_path(char **env);
void	free_struct(t_list *pipex);
void	child(t_list pipex, char **av, char **env);
void	creat_pipes(t_list *pipex);
void	dup_files(int fd1, int fd2);
void	cmd_error(t_list *pipex);
char	*get_cmd_path(t_list pipex);
void	increment(t_list *pipex);
void	close_pipes(t_list *pipex);
void	close_infile_outfile(t_list *pipex);

#endif