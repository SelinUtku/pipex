/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 05:10:55 by sutku             #+#    #+#             */
/*   Updated: 2022/10/22 01:05:47 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	head(char const *s, char const *set)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[counter] != '\0' && set[i] != '\0')
	{
		if (set[i] == s[counter])
		{	
			counter++;
			i = -1;
		}
		i++;
	}
	return (counter);
}

int	tail(char const *s, char const *set)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(s) - 1;
	while (len >= 0 && set[i] != '\0')
	{
		if (set[i] == s[len])
		{
			len--;
			i = -1;
		}
		i++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*arr;
	int		i;
	int		ind1;
	int		ind2;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	ind1 = head(s1, set);
	ind2 = tail(s1, set);
	if (ind2 > ind1)
		arr = malloc((ind2 - ind1 + 2) * sizeof(char));
	else
		arr = malloc(1 * sizeof(char));
	if (!arr)
		return (NULL);
	while (ind1 < ind2 + 1)
	{
		arr[i] = s1[ind1];
		i++;
		ind1++;
	}
	arr[i] = '\0';
	return (arr);
}
