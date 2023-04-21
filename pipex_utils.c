/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:51:39 by sutku             #+#    #+#             */
/*   Updated: 2023/04/21 04:39:22 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

void	error_message(char **argv, char *s, int flag)
{
	ft_putstr_fd(&argv[0][2], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(argv[flag], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
}

int	open_file(char *argv, char **argv2, int file_n, t_pipe *p)
{
	int	fd;

	if (file_n == 1 && p->heredoc_status == 0)
		fd = open(argv, O_RDONLY);
	else
	{
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

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_double_int(int **str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_strndup(char *str, int len)
{
	int		i;
	int		j;
	char	*arr;

	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
	{
		perror("malloc");
		return (NULL);
	}
	i = -1;
	j = 0;
	while (++i < len)
	{
		if (str[i + j] == '\\')
			j++;
		arr[i] = str[i + j];
	}
	arr[i] = '\0';
	return (arr);
}
