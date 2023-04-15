/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:10:36 by sutku             #+#    #+#             */
/*   Updated: 2023/04/16 00:08:47 by sutku            ###   ########.fr       */
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

typedef struct s_pipe
{
	char	**command1;
	char	**command2;
	char	*path;
	char	**env_paths;
	pid_t	*pid;
	int		**pipes;
	int		status;
	int		fd1;
	int		fd2;
	int		n_argc;
	int		num;
}t_pipe;

char	*real_command_path(t_pipe *p, char *command);
void	envp_path(t_pipe *p, char **envp);
char	*command_path(t_pipe *p, char *command);
void	error_message(char **argv, char *s, int flag);
int		open_file(char *argv, char **argv2, int file_n);
char	**create_command(char *str);
char	**parse_command(char *str, char **par_comm);
void	close_pipes(t_pipe *p, int i);
void	open_pipes(t_pipe *p);
void	close_main_pipes(t_pipe *p);
void	calling_childs(t_pipe *p, char **argv, char **envp);
void	first_child(t_pipe *p, char **argv, char **envp, int i);
void	last_child(t_pipe *p, char **argv, char **envp, int i);
void	middle_child(t_pipe *p, char **argv, char **envp, int i);
void	wait_all_child(t_pipe *p);

#endif
