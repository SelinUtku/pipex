/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:43:22 by sutku             #+#    #+#             */
/*   Updated: 2023/04/14 17:14:31 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *ft_strndup(char *str, int len)
{
	int	i;
	int	j;
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
char	**create_command(char *str)
{
	int		i;
	int		len;
	int		pos;
	int		word_counter;
	char	**par_comm;

	i = 0;
	len = 0;
	word_counter = 0;
	while (str[i] != '\0')
	{
		len = 0;
		if (str[i] == '\'' || str[i] == '\"')
		{
			word_counter++;
			pos = str[i];
			i++;
			while (str[i] != pos && str[i] != '\0')
			{
				if (str[i] == '\\')
					i++;
				i++;
				len++;
			}
			if (str[i] == pos)
				i++;
		}
		else if (str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '\0')
		{
			word_counter++;
			while (str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '\0')
			{
				if (str[i] == '\\')
					i++;
				i++;
				len++;
			}
		}
		while (str[i] == ' ' && str[i] != '\0')
			i++;
	}
	par_comm = (char **)malloc(sizeof(char *) * (word_counter + 1));
	return (parse_command(str, par_comm));
}

char	**parse_command(char *str, char **par_comm)
{
	int		i;
	int		j;
	int		len;
	char	pos;
	char	*temp;

	i = 0;
	len = 0;
	j = 0;
	while (str[i] != '\0')
	{
		len = 0;
		if (str[i] == '\'' || str[i] == '\"')
		{
			pos = str[i];
			i++;
			temp = str + i;
			while (str[i] != pos && str[i] != '\0')
			{
				if (str[i] == '\\')
					i++;
				i++;
				len++;
			}
			par_comm[j] = ft_strndup(temp, len);
			j++;
			if (str[i] == pos)
				i++;
		}
		else if (str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '\0')
		{
			temp = str + i;
			while (str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '\0')
			{
				if (str[i] == '\\')
					i++;
				i++;
				len++;
			}
			par_comm[j] = ft_strndup(temp, len);
			j++;
		}
		while (str[i] == ' ' && str[i] != '\0')
			i++;
	}
	par_comm[j] = NULL;
	return (par_comm);
}

