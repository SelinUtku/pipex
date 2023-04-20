/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 05:43:38 by sutku             #+#    #+#             */
/*   Updated: 2023/04/20 05:45:50 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fd_fails(char **argv2, int file_n, t_pipe *p)
{
	ft_putstr_fd(&argv2[0][2], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(argv2[file_n], 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	all_free(p);
	exit(errno);
}
