/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:51:39 by sutku             #+#    #+#             */
/*   Updated: 2023/04/21 05:52:47 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file_b(char *argv, char **argv2, int file_n, t_pipe *p)
{
	int	fd;

	if (file_n == 1 && p->heredoc_status == 0)
		fd = open(argv, O_RDONLY);
	else if (p->heredoc_status == 1 && file_n == 1)
		fd = open("heredoc_file", O_RDONLY);
	else
	{
		if (p->heredoc_status == 1)
			fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (access(argv, W_OK) != 0)
		{
			all_free(p);
			exit(EXIT_FAILURE);
		}
	}
	if (fd < 0)
		fd_fails(argv2, file_n, p);
	return (fd);
}
