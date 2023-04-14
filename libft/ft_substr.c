/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:37:15 by sutku             #+#    #+#             */
/*   Updated: 2022/10/22 01:41:13 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*arr;
	size_t			i;
	size_t			len_s;

	i = 0;
	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
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
	return (arr);
}
