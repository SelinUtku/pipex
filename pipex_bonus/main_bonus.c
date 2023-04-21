/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 04:36:52 by sutku             #+#    #+#             */
/*   Updated: 2023/04/21 06:34:29 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	p;

	p.path = NULL;
	p.n_argc = argc;
	p.heredoc_status = 0;
	if (argc >= 5)
	{
		envp_path(&p, envp);
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			p.n_argc = argc - 1;
			p.heredoc_status = 1;
			here_doc(argv);
		}
		open_pipes(&p);
		calling_childs_b(&p, argv, envp);
		close_main_pipes(&p);
		wait_all_child_b(&p);
	}
	else
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
