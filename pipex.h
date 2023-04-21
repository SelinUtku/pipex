/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:10:36 by sutku             #+#    #+#             */
/*   Updated: 2023/04/21 03:20:48 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "ftprintf/ft_printf.h"
# include "gnl/get_next_line.h"

typedef struct s_pipe
{
	char	**command;
	char	**env_paths;
	int		**pipes;
	char	*path;
	char	*com_path;
	pid_t	*pid;
	int		status;
	int		fd1;
	int		fd2;
	int		n_argc;
	int		heredoc_status;
}t_pipe;

typedef struct s_parse
{
	int		i;
	int		j;
	int		len;
	int		word_counter;
	char	*temp;
	char	**par_comm;
}t_parse;

//finding paths
char	*real_command_path(t_pipe *p, char *command);
void	envp_path(t_pipe *p, char **envp);
char	*command_path(t_pipe *p, char *command);
// utils
void	error_message(char **argv, char *s, int flag);
int		open_file(char *argv, char **argv2, int file_n, t_pipe *p);
void	free_double(char **str);
void	free_double_int(int **str, int len);
void	here_doc(char **argv);
void	all_free(t_pipe *p);
void	fd_fails(char **argv2, int file_n, t_pipe *p);
//parsing
char	**command_counter(char *str);
void	command_counter_util(char *str, t_parse *prs);
char	**parse_command(char *str, int comm_len);
void	parse_command_util(char *str, t_parse *par);
void	parse_command_util2(char *str, t_parse *par);
char	*ft_strndup(char *str, int len);
//pipes
void	close_pipes(t_pipe *p, int i);
void	open_pipes(t_pipe *p);
void	close_main_pipes(t_pipe *p);
//child process
void	calling_childs(t_pipe *p, char **argv, char **envp);
void	first_child(t_pipe *p, char **argv, char **envp, int i);
void	last_child(t_pipe *p, char **argv, char **envp, int i);
void	middle_child(t_pipe *p, char **argv, char **envp, int i);
void	wait_all_child(t_pipe *p);

#endif
