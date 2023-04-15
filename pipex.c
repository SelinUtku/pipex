/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:45:31 by sutku             #+#    #+#             */
/*   Updated: 2023/04/15 04:07:04 by sutku            ###   ########.fr       */
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
	if (command[0] == '.' || ft_strchr(command, '/') != NULL)
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

void	first_child(t_pipe *p, char **argv, int **pipes, char **envp, int i)
{
	int	j;

	close(pipes[0][0]);
	p->command1 = create_command(argv[2]);
	p->fd1 = open_file(argv[1], argv, 1);
	if (dup2(pipes[0][1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(pipes[0][1]);
	if (dup2(p->fd1, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->fd1);
	if (command_path(p, p->command1[0]) == NULL)
	{
		error_message(argv, "command not found", 2);
		exit(127);
	}
	j = -1;
	while (++j < p->n_argc - 4)
	{
		if (i != j)
			close(pipes[j][0]);
		if (i + 1 != j)
			close(pipes[j][1]);
	}
	execve(command_path(p, p->command1[0]), p->command1, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	last_child(t_pipe *p, char **argv, int **pipes, char **envp, int i)
{
	int	j;

	close(pipes[i][1]);
	p->fd2 = open_file(argv[p->n_argc - 1], argv, i + 3);
	if (dup2(pipes[i][0], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(pipes[i][0]);
	if (dup2(p->fd2, STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->fd2);
	p->command2 = create_command(argv[p->n_argc - 2]);
	if (command_path(p, p->command2[0]) == NULL)
	{
		error_message(argv, "command not found", p->n_argc - 2);
		exit(127);
	}
	j = -1;
	while (++j < p->n_argc - 4)
	{
		if (i != j)
			close(pipes[j][0]);
		if (i + 1 != j)
			close(pipes[j][1]);
	}
	execve(command_path(p, p->command2[0]), p->command2, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	middle_child(t_pipe *p, char **argv, int **pipes, char **envp, int i)
{
	int	j;

	if (dup2(pipes[i][0], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(pipes[i][1]);
	if (dup2(pipes[i + 1][1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(pipes[i + 1][1]);
	p->command2 = create_command(argv[i + 3]);
	if (command_path(p, p->command2[0]) == NULL)
	{
		error_message(argv, "command not found", i + 3);
		exit(127);
	}
	j = -1;
	while (++j < p->n_argc - 4)
	{
		if (i != j)
			close(pipes[j][0]);
		if (i + 1 != j)
			close(pipes[j][1]);
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
	pid_t	*pid;
	int		i;
	int		j;
	int		**pipes;
	int		status;

	// atexit(leaks);

	p.c1_path = NULL;
	p.c2_path = NULL;
	p.path = NULL;
	p.n_argc = argc;
	if (argc >= 5)
	{
		pipes = malloc((argc - 4) * sizeof(int *));
		pid = malloc((argc - 3) * sizeof(int));
		i = -1;
		envp_path(&p, envp);
		while (++i < argc - 4)
		{
			pipes[i] = malloc (sizeof(int) * 2);
			if (pipe(pipes[i]) < 0)
				exit(EXIT_FAILURE);
		}
		i = -1;
		while (++i < argc - 3)
		{
			pid[i] = fork();
			if (pid[i] < 0)
				exit(EXIT_FAILURE);
			if (pid[i] == 0)
			{
				if (i == 0)
					first_child(&p, argv, pipes, envp, i);
				else if (i == argc - 4)
					last_child(&p, argv, pipes, envp, i - 1);
				else
					middle_child(&p, argv, pipes, envp, i - 1);
			}
		}
		i = -1;
		while (++i < argc - 4)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i = -1;
		while (++i < argc - 3)
			waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			exit(WEXITSTATUS(status));
	}
	else
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
