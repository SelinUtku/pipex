/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:15:29 by sutku             #+#    #+#             */
/*   Updated: 2023/04/21 04:26:58 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(char **argv)
{
	char	*arr;
	int		len;
	int		fd;

	len = 0;
	fd = open("heredoc_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	arr = NULL;
	if (fd < 0)
		exit(errno);
	while (1)
	{
		ft_printf("here_doc >");
		arr = get_next_line(STDIN_FILENO);
		len = ft_strlen(arr);
		if (ft_strncmp(arr, argv[2], len - 1) == 0 \
			&& len - 1 == ft_strlen(argv[2]))
		{	
			free(arr);
			break ;
		}
		ft_putstr_fd(arr, fd);
		free(arr);
	}
	close(fd);
}
