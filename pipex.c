/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:45:31 by sutku             #+#    #+#             */
/*   Updated: 2023/04/16 06:39:25 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	p;

	p.path = NULL;
	p.n_argc = argc;
	if (argc >= 5)
	{
		envp_path(&p, envp);
		open_pipes(&p);
		calling_childs(&p, argv, envp);
		close_main_pipes(&p);
		wait_all_child(&p);
	}
	else
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
