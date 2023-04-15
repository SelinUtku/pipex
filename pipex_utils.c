/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:51:39 by sutku             #+#    #+#             */
/*   Updated: 2023/04/16 00:12:27 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	error_message(char **argv, char *s, int flag)
{
	ft_putstr_fd(&argv[0][2], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(argv[flag], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
}

int	open_file(char *argv, char **argv2, int file_n)
{
	int	fd;

	if (file_n == 1)
		fd = open(argv, O_RDONLY);
	else
	{
		fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (access(argv, W_OK) != 0)
			exit(EXIT_FAILURE);
	}
	if (fd < 0)
	{
		ft_putstr_fd(&argv2[0][2], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(argv2[file_n], 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		exit(errno);
	}
	return (fd);
}

void	free_double(char **str)
{
	int	i;

	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
