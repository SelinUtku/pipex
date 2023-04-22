/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:10:36 by sutku             #+#    #+#             */
/*   Updated: 2023/04/22 02:59:30 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../pipex.h"

void	here_doc(char **argv);
int		open_file_b(char *argv, char **argv2, int file_n, t_pipe *p);

//child process
void	calling_childs_b(t_pipe *p, char **argv, char **envp);
void	first_child_b(t_pipe *p, char **argv, char **envp, int i);
void	last_child_b(t_pipe *p, char **argv, char **envp, int i);
void	middle_child_b(t_pipe *p, char **argv, char **envp, int i);
void	wait_all_child_b(t_pipe *p);

#endif
