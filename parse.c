/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:43:22 by sutku             #+#    #+#             */
/*   Updated: 2023/04/17 01:20:44 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	command_counter_util(char *str, t_parse *par)
{
	int	pos;

	par->word_counter++;
	pos = str[par->i];
	par->i++;
	while (str[par->i] != pos && str[par->i] != '\0')
	{
		if (str[par->i] == '\\')
			par->i++;
		par->i++;
	}
	if (str[par->i] == pos)
		par->i++;
}

char	**command_counter(char *str)
{
	t_parse	par;

	par.i = 0;
	par.word_counter = 0;
	while (str[par.i] != '\0')
	{
		if (str[par.i] == '\'' || str[par.i] == '\"')
			command_counter_util(str, &par);
		else if (str[par.i] != '\'' && str[par.i] != '\"'
			&& str[par.i] != ' ' && str[par.i] != '\0')
		{
			par.word_counter++;
			while (str[par.i] != '\'' && str[par.i] != '\"'
				&& str[par.i] != ' ' && str[par.i] != '\0')
			{
				if (str[par.i] == '\\')
					par.i++;
				par.i++;
			}
		}
		while (str[par.i] == ' ' && str[par.i] != '\0')
			par.i++;
	}
	par.par_comm = (char **)malloc(sizeof(char *) * (par.word_counter + 1));
	return (parse_command(str, par.par_comm));
}

void	parse_command_util(char *str, t_parse *par)
{
	char	pos;

	pos = str[par->i];
	par->i++;
	par->temp = str + par->i;
	while (str[par->i] != pos && str[par->i] != '\0')
	{
		if (str[par->i] == '\\')
			par->i++;
		par->i++;
		par->len++;
	}
	par->par_comm[par->j] = ft_strndup(par->temp, par->len);
	par->j++;
	if (str[par->i] == pos)
		par->i++;
}

void	parse_command_util2(char *str, t_parse *par)
{
	par->temp = str + par->i;
	while (str[par->i] != '\'' && str[par->i] != '\"'
		&& str[par->i] != ' ' && str[par->i] != '\0')
	{
		if (str[par->i] == '\\')
			par->i++;
		par->i++;
		par->len++;
	}
	par->par_comm[par->j] = ft_strndup(par->temp, par->len);
	par->j++;
}

char	**parse_command(char *str, char **command)
{
	t_parse	par;

	par.i = 0;
	par.j = 0;
	par.par_comm = command;
	while (str[par.i] != '\0')
	{
		par.len = 0;
		if (str[par.i] == '\'' || str[par.i] == '\"')
			parse_command_util(str, &par);
		else if (str[par.i] != '\'' && str[par.i] != '\"'
			&& str[par.i] != ' ' && str[par.i] != '\0')
			parse_command_util2(str, &par);
		while (str[par.i] == ' ' && str[par.i] != '\0')
			par.i++;
	}
	par.par_comm[par.j] = NULL;
	return (par.par_comm);
}
