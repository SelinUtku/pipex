/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:45:31 by sutku             #+#    #+#             */
/*   Updated: 2023/04/14 17:07:09 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

void	envp_path(t_pipe *p, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			p->path = (envp[i] + 5);
			p->env_paths = ft_split(p->path, ':');
			return ;
		}
		i++;
	}
	p->path = ("/usr/bin");
	p->env_paths = ft_split(p->path, ':');
}

char	*command_path(t_pipe *p, char *command)
{
	if (command[0] == '.' || ft_strchr(command,'/') != NULL)
	{
		if (access(command, F_OK) == 0)
		{
			if (access(command, X_OK) == 0)
				return (command);
			else
				exit(126);
		}
		return (NULL);
	}
	return (real_command_path(p, command));
}

void	first_child(t_pipe *p, char **argv, int *pipes, char **envp)
{
	close(pipes[0]);
	p->command1 = create_command(argv[2]);
	p->fd1 = open_file(argv, 1);
	if (dup2(pipes[1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(pipes[1]);
	if (dup2(p->fd1, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->fd1);
	if (command_path(p, p->command1[0]) == NULL)
	{
		error_message(argv, "command not found", 2);
		exit(127);
	}
	execve(command_path(p, p->command1[0]), p->command1, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	second_child(t_pipe *p, char **argv, int *pipes, char **envp)
{
	close(pipes[1]);
	p->fd2 = open_file(argv, 4);
	if (dup2(pipes[0], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(pipes[0]);
	if (dup2(p->fd2, STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->fd2);
	p->command2 = create_command(argv[3]);
	if (command_path(p, p->command2[0]) == NULL)
	{
		error_message(argv, "command not found", 3);
		exit(127);
	}
	execve(command_path(p, p->command2[0]), p->command2, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void leaks()
{
	system("leaks pipex");
}

int main (int argc, char **argv, char **envp)
{
	t_pipe	p;
	pid_t	pid1;
	pid_t	pid2;
	int		pipes[2];
	int		status;

	// atexit(leaks);
	// p.c1_path = NULL;
	// p.c2_path = NULL;
	// p.path = NULL;
	if (argc == 5)
	{
		envp_path(&p, envp);
		if (pipe(pipes) < 0)
			exit(EXIT_FAILURE);//perror
		pid1 = fork();
		if (pid1 < 0)
			exit(EXIT_FAILURE);
		if (pid1 == 0)//child1
			first_child(&p, argv, pipes, envp);
		pid2 = fork();
		if (pid2 < 0)
			exit(EXIT_FAILURE);
		if (pid2 == 0)//child2
			second_child(&p, argv, pipes, envp);
		close(pipes[0]);
		close(pipes[1]);
		waitpid(pid1, &status, 0);
		waitpid(pid2, &status, 0);
		if (WIFEXITED(status))
			exit(WEXITSTATUS(status));
	}
	else
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
