/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 00:12:07 by sutku             #+#    #+#             */
/*   Updated: 2023/04/16 00:13:34 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	envp_path(t_pipe *p, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			p->path = (envp[i] + 5);
			p->env_paths = ft_split(p->path, ':');
			return ;
		}
		i++;
	}
	p->path = ("/usr/bin");
	p->env_paths = ft_split(p->path, ':');
}

char	*command_path(t_pipe *p, char *command)
{
	if (command[0] == '.' || ft_strchr(command, '/') != NULL)
	{
		if (access(command, F_OK) == 0)
		{
			if (access(command, X_OK) == 0)
				return (command);
			else
				exit(126);
		}
		return (NULL);
	}
	return (real_command_path(p, command));
}

char	*real_command_path(t_pipe *p, char *command)
{
	char	*tmp;
	char	*comm_path;
	int		i;

	i = 0;
	while (p->env_paths && p->env_paths[i])
	{
		comm_path = ft_strjoin(p->env_paths[i], "/");
		tmp = comm_path;
		comm_path = ft_strjoin(tmp, command);// maybe leak
		free(tmp);
		if (access(comm_path, F_OK) == 0)
		{
			if (access(comm_path, X_OK) == 0)
				return (comm_path);
		}
		else
			free(comm_path);
		i++;
	}
	return (NULL);
}