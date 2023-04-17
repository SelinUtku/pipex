/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:48:48 by sutku             #+#    #+#             */
/*   Updated: 2023/02/07 14:25:29 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char			*arr;
	size_t			i;
	size_t			len_s;

	i = 0;
	len_s = ft_strlen_gnl(s);
	if (start > len_s)
		len = 0;
	if (len_s - start <= len)
		len = len_s - start;
	arr = malloc((len + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		arr[i] = s[start + i];
		i++;
	}
	arr[i] = '\0';
	if (s)
		free(s);
	return (arr);
}

char	*ft_strjoin_gnl(char *s1, char *s2, int ct)
{
	int		i;
	int		j;
	char	*arr;

	arr = malloc((ft_strlen_gnl(s1) + ct + 1) * sizeof(char));
	if (!arr)
		return (0);
	i = 0;
	j = 0;
	while (s1 && s1[i] != '\0')
	{
		arr[i] = s1[i];
		i++;
	}
	while (s2 && j < ct)
	{
		arr[i + j] = s2[j];
		j++;
	}
	arr[i + j] = '\0';
	if (s1)
		free(s1);
	return (arr);
}

void	my_malloc(char **buff)
{
	*buff = NULL;
	*buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buff)
		return ;
}
