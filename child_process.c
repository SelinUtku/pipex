/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:46:01 by sutku             #+#    #+#             */
/*   Updated: 2023/04/17 01:15:33 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipe *p, char **argv, char **envp, int i)
{
	close(p->pipes[0][0]);
	p->command1 = command_counter(argv[2]);
	p->fd1 = open_file(argv[1], argv, 1);
	if (dup2(p->pipes[0][1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->pipes[0][1]);
	if (dup2(p->fd1, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->fd1);
	if (command_path(p, p->command1[0]) == NULL)
	{
		error_message(argv, "command not found", 2);
		exit(127);
	}
	close_pipes(p, i);
	execve(command_path(p, p->command1[0]), p->command1, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	last_child(t_pipe *p, char **argv, char **envp, int i)
{
	close(p->pipes[i][1]);
	p->fd2 = open_file(argv[p->n_argc - 1], argv, i + 3);
	if (dup2(p->pipes[i][0], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->pipes[i][0]);
	if (dup2(p->fd2, STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->fd2);
	p->command2 = command_counter(argv[p->n_argc - 2]);
	if (command_path(p, p->command2[0]) == NULL)
	{
		error_message(argv, "command not found", p->n_argc - 2);
		exit(127);
	}
	close_pipes(p, i);
	execve(command_path(p, p->command2[0]), p->command2, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	middle_child(t_pipe *p, char **argv, char **envp, int i)
{
	if (dup2(p->pipes[i][0], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->pipes[i][1]);
	if (dup2(p->pipes[i + 1][1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->pipes[i + 1][1]);
	p->command2 = command_counter(argv[i + 3]);
	if (command_path(p, p->command2[0]) == NULL)
	{
		error_message(argv, "command not found", i + 3);
		exit(127);
	}
	close_pipes(p, i);
	execve(command_path(p, p->command2[0]), p->command2, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	calling_childs(t_pipe *p, char **argv, char **envp)
{
	int	i;

	p->pid = malloc((p->n_argc - 3) * sizeof(int));
	i = -1;
	while (++i < p->n_argc - 3)
	{	
		p->pid[i] = fork();
		if (p->pid[i] < 0)
			exit(EXIT_FAILURE);
		if (p->pid[i] == 0)
		{
			if (i == 0)
				first_child(p, argv, envp, i);
			else if (i == p->n_argc - 4)
				last_child(p, argv, envp, i - 1);
			else
				middle_child(p, argv, envp, i - 1);
		}
	}
}

void	wait_all_child(t_pipe *p)
{
	int	i;

	i = -1;
	while (++i < p->n_argc - 3)
		waitpid(p->pid[i], &p->status, 0);
	if (WIFEXITED(p->status))
		exit(WEXITSTATUS(p->status));
}
