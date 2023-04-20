/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:46:01 by sutku             #+#    #+#             */
/*   Updated: 2023/04/20 05:48:36 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipe *p, char **argv, char **envp, int i)
{
	p->fd1 = open_file(argv[1], argv, 1, p);
	if (p->heredoc_status == 1)
		p->command = command_counter(argv[i + 3]);
	else
		p->command = command_counter(argv[i + 2]);
	if (dup2(p->pipes[0][1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->pipes[0][1]);
	if (dup2(p->fd1, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->fd1);
	close_main_pipes(p);
	p->com_path = command_path(p, p->command[0]);
	if (p->com_path == NULL)
	{
		error_message(argv, "command not found", 2);
		all_free(p);
		free_double(p->command);
		exit(127);
	}
	execve(p->com_path, p->command, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	last_child(t_pipe *p, char **argv, char **envp, int i)
{
	if (p->heredoc_status == 1)
		p->fd2 = open_file(argv[p->n_argc], argv, i + 4, p);
	else
		p->fd2 = open_file(argv[p->n_argc - 1], argv, i + 3, p);
	if (dup2(p->pipes[i][0], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	if (dup2(p->fd2, STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(p->fd2);
	if (p->heredoc_status == 1)
		p->command = command_counter(argv[p->n_argc - 1]);
	else
		p->command = command_counter(argv[p->n_argc - 2]);
	close_main_pipes(p);
	p->com_path = command_path(p, p->command[0]);
	if (p->com_path == NULL)
	{
		error_message(argv, "command not found", p->n_argc - 2);
		all_free(p);
		free_double(p->command);
		exit(127);
	}
	execve(p->com_path, p->command, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	middle_child(t_pipe *p, char **argv, char **envp, int i)
{
	if (dup2(p->pipes[i][0], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	if (dup2(p->pipes[i + 1][1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	if (p->heredoc_status == 1)
		p->command = command_counter(argv[i + 4]);
	else
		p->command = command_counter(argv[i + 3]);
	close_main_pipes(p);
	p->com_path = command_path(p, p->command[0]);
	if (p->com_path == NULL)
	{
		error_message(argv, "command not found", i + 3);
		all_free(p);
		free_double(p->command);
		exit(127);
	}
	execve(p->com_path, p->command, envp);
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
		{
			free(p->pid);
			exit(EXIT_FAILURE);
		}
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
	all_free(p);
	if (p->heredoc_status == 1)
		unlink("heredoc_file");
	if (WIFEXITED(p->status))
		exit(WEXITSTATUS(p->status));
}
