/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:10:42 by sutku             #+#    #+#             */
/*   Updated: 2023/02/07 14:26:17 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_newline(char *buff)
{
	int	i;

	i = 0;
	while (buff && buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*remain_part(char *s_arr, char **line, int *flag)
{
	int	a;
	int	len;

	len = ft_strlen_gnl(s_arr);
	a = check_newline(s_arr);
	if (a == len)
	{
		*line = ft_strjoin_gnl(*line, s_arr, len);
		free(s_arr);
		return (NULL);
	}
	else
	{
		*line = ft_strjoin_gnl(*line, s_arr, a + 1);
		s_arr = ft_substr_gnl(s_arr, a + 1, len - a);
		*flag = 1;
		return (s_arr);
	}
}

char	*check_valid(int control, char *s_arr, char *line, char *buff)
{
	if (control == 0)
	{
		free(s_arr);
		free(buff);
		if (line && !*line)
		{
			free(line);
			line = NULL;
		}
		return (line);
	}
	else if (control == -1)
	{
		free(s_arr);
		free(buff);
		if (line)
			free(line);
		return (NULL);
	}
	return (NULL);
}

char	*my_get_line(int control, char **s_arr, char **line, char *buff)
{
	int	a;

	if (control == 0 || control == -1)
		return (check_valid(control, *s_arr, *line, buff));
	buff[control] = '\0';
	a = check_newline(buff);
	if (a == control)
	{
		*line = ft_strjoin_gnl(*line, buff, control);
		return (NULL);
	}
	else
	{
		*line = ft_strjoin_gnl(*line, buff, a + 1);
		*s_arr = ft_substr_gnl(buff, a + 1, control - a);
		return (*line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	int			control;
	char		*buff;
	static char	*s_arr;
	char		*line;
	int			flag;

	line = NULL;
	flag = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (s_arr)
	{
		s_arr = remain_part(s_arr, &line, &flag);
		if (flag == 1)
			return (line);
	}
	control = 1;
	my_malloc(&buff);
	while (control > 0)
	{
		control = read(fd, buff, BUFFER_SIZE);
		if (my_get_line(control, &s_arr, &line, buff))
			return (line);
	}
	return (NULL);
}
