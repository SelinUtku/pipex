/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:58:04 by sutku             #+#    #+#             */
/*   Updated: 2023/04/16 00:16:05 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_pipes(t_pipe *p)
{
	int	i;

	i = -1;
	p->pipes = malloc((p->n_argc - 4) * sizeof(int *));
	while (++i < p->n_argc - 4)
	{
		p->pipes[i] = malloc (sizeof(int) * 2);
		if (pipe(p->pipes[i]) < 0)
			exit(EXIT_FAILURE);
	}
}

void	close_main_pipes(t_pipe *p)
{
	int	i;

	i = -1;
	while (++i < p->n_argc - 4)
	{
		close(p->pipes[i][0]);
		close(p->pipes[i][1]);
	}
}

void	close_pipes(t_pipe *p, int i)
{
	int	j;

	j = -1;
	while (++j < p->n_argc - 4)
	{
		if (i != j)
			close(p->pipes[j][0]);
		if (i + 1 != j)
			close(p->pipes[j][1]);
	}
}
