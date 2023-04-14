/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 05:38:49 by sutku             #+#    #+#             */
/*   Updated: 2022/10/24 03:51:12 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	word_len(char const *s, unsigned int i, char c)
{
	int	word;

	word = 0;
	while (s[i + word] != '\0' && s[i + word] != c)
		word++;
	return (word);
}

static unsigned int	word_counter(char const *s, char c)
{
	unsigned int	counter;
	unsigned int	i;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			counter++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (counter);
}

void	sub_writer(char const *s, unsigned int i, char *ptr, char c)
{
	unsigned int	j;

	j = 0;
	while (j < word_len(s, i, c))
	{
		ptr[j] = s[i + j];
		j++;
	}
	ptr[j] = '\0';
}

void	*memory_free(char **ptr, unsigned int i)
{
	unsigned int	j;

	j = 0;
	while (j < i)
	{
		free(ptr[j]);
		j++;
	}
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	char			**arr;

	if (!s)
		return (NULL);
	arr = (char **)malloc((word_counter(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < word_counter(s, c))
	{
		while (s[j] == c)
			j++;
		arr[i] = (char *)malloc((word_len(s, j, c) + 1) * sizeof(char));
		if (!arr[i])
			return (memory_free(arr, i));
		sub_writer(s, j, arr[i], c);
		j += word_len(s, j, c);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
